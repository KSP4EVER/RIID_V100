import serial
import sys
import matplotlib.pyplot as plt
import numpy as np
import re
import random
import threading
import time
import serial.tools.list_ports
import os


buffer_size = 1024  # Number of data points to collect
data_buffer = [0]*buffer_size # data buffer to store the data from the device

# locking objects
data_lock = threading.Lock()
stop_event = threading.Event()
data_ready_event = threading.Event()


# graph updater
def updatePlot():
    global buffer_size
    global data_buffer
    plt.ion()  # Turn on interactive mode
    fig, ax = plt.subplots()
    line, = ax.plot([], [], '-k')  # Create a line plot

    ax.set_xlim(0, buffer_size - 1)
    ax.set_ylim(0, 500)  # Set the expected range of the data (adjust as needed)
    ax.set_title("Serial Data Plot")
    ax.set_xlabel("Sample Number")
    ax.set_ylabel("Value")
    ax.set_ylim(1, 1e6)
    plt.grid(True)
    plt.minorticks_on()
    plt.yscale('log')
    plt.autoscale(True)

    while not stop_event.is_set():
        line.set_xdata(range(buffer_size))
        line.set_ydata(data_buffer)
        

        ax.set_ylim(1, max(data_buffer) + 100)

        plt.draw()                
        plt.pause(1)  
        #time.sleep(1)

# com port handler
def SerialCom():
    # Configure the serial connection parameters
    global buffer_size
    global data_buffer

    ports = serial.tools.list_ports.comports()

    if not ports:
        print("No COM ports found.")
    else:
        print("Available COM ports:")
        for port in ports:
            print(f"{port.device} - {port.description}")

    com_port = input("Enter the COM port (e.g., COM3 or /dev/ttyUSB0): ")
   # com_port = "COM14"
    baud_rate = 115200  # You can adjust the baud rate as needed
    ser = serial.Serial(com_port, baud_rate, timeout=1)
    print(f"Opened {com_port} successfully.")


    print("Collecting data. Press Ctrl+C to exit.")
    try:
        while not stop_event.is_set():
            # Read a line from the serial port
            data = ser.readline().strip().decode('utf-8')
            #print(data)
            # If data is received, try to parse it as a float
            if data:
                try:
                    index_s, value_s = data.split(":")
                    #print(index_s)
                    #print(value_s)
                    index = int(re.findall(r'\d+\.?\d*', index_s)[0])
                    value = int(re.findall(r'\d+\.?\d*', value_s)[0])

                    data_buffer[index] = value
                    #print(f"Buffer[{index}]:{data_buffer[index]}")
                
                    if  index == buffer_size-1 :
                        #print("asd")
                        local_time = time.localtime()
                        formatted_time = time.strftime("%H:%M:%S", local_time)
                        print(f"[{formatted_time}] Received {index + 1} packets...")
                        data_ready_event.set()

                except ValueError:
                    #print("Cannot convert  to an integer.")
                    pass
                #except KeyboardInterrupt:
                #    print("\nExiting...")

    except serial.SerialException as e:
        print(f"Error: Could not open {com_port}. {e}")
        sys.exit(1)

    finally:
        # Close the serial connection if it was opened
        if 'ser' in locals() and ser.is_open:
            ser.close()
            print("Serial connection closed.")


def save_data_periodiccaly(name,period):
    ticks_to_save = period
    while not stop_event.is_set():
        time.sleep(1)

        if ticks_to_save == 0:
            ticks_to_save = period
        
            local_time = time.localtime()
            file_name = f'{name}_snapshot_{time.strftime("%H-%M-%S", local_time)}.txt'
            print(f"Saving to {file_name}")
            channel_num = 0
            with open(file_name,'w') as file:
                for value in data_buffer:
                    channel_num = channel_num + 1
                    file.write(f'{channel_num}:{value}\n')
            print(f"Data saved to: {file_name}")
        else:
            ticks_to_save = ticks_to_save - 1
        #time.sleep(1)


def main():

    try:

        # Prevent the system from sleeping

        thread_serial = threading.Thread(target=SerialCom)
        
        save_periodically = input("Save the data periodiccaly [y/n]:")
        save_periodically_name = ""
        period_time = 0

        if save_periodically == "y" or save_periodically == "Y":
            period_time = 60*int(input("Give the period time in minute [min]:"))
            save_folder_name = input("Add the name of the folder that stores the snapshots:")
            save_periodically_name = input("Add name to data [name_snapshot_timecode]:")

            save_periodically_name = f'{save_folder_name}/{save_periodically_name}'
            
            os.makedirs(save_folder_name)
            print(f"Folder '{save_folder_name}' created successfully.")

            add_meas_desc = input("Do you want to add measurment description file [y/n]:")
            if add_meas_desc == "y" or add_meas_desc == "Y":
                meas_desc = input("Measurment description:")
                with open(f'{save_periodically_name}_measurment_description.txt','w') as file:
                    file.write(f'{meas_desc}')


        # thread_plot.start()
        thread_period_data_saver = threading.Thread(target=save_data_periodiccaly,args=(save_periodically_name,period_time,))
        
        
        if period_time != 0:
            thread_period_data_saver.start()

        thread_serial.start()
        updatePlot()

        while True:
            if data_ready_event.is_set(): 
                updatePlot()
                data_ready_event.clear()
            time.sleep(1)
     

        #thread_plot.join()
    except FileExistsError:
        print(f"Folder '{save_folder_name}' already exists.")
        main()
    except KeyboardInterrupt:
        stop_event.set()
        thread_serial.join()
        if period_time != 0:
            thread_period_data_saver.join()
        
    finally:

        save_to_file = input("Save to the measured data to .txt [y/n]:")

        if save_to_file == "y" or save_to_file == "Y":
            file_name = input("filename:")
            print(f"Saving to {file_name}")
            channel_num = 0
            with open(file_name,'w') as file:
                for value in data_buffer:
                    channel_num = channel_num + 1
                    file.write(f'{channel_num}:{value}\n')
            print(f"Data saved to: {file_name}")
        
        print("Exiting from application")
        

        plt.ioff()
        plt.close()
    

if __name__ == "__main__":
    main()




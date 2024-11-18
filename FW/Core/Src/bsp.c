/*
 * bsp.c
 *
 *  Created on: Nov 12, 2024
 *      Author: Misi
 */

#include "bsp.h"

double remaining_capacity_lut[] = {
    0.035, 0.042, 0.049, 0.059, 0.070, 0.079, 0.089, 0.099,
    0.112, 0.126, 0.142, 0.159, 0.177, 0.196, 0.217, 0.241,
    0.271, 0.302, 0.336, 0.370, 0.403, 0.437, 0.471, 0.508,
    0.546, 0.584, 0.623, 0.661, 0.699, 0.737, 0.776, 0.814,
    0.852, 0.890, 0.928, 0.967, 1.005, 1.043, 1.081, 1.120,
    1.158, 1.196, 1.234, 1.272, 1.311, 1.349, 1.387, 1.425,
    1.464, 1.502, 1.540, 1.578, 1.616, 1.655, 1.693, 1.731,
    1.769, 1.807, 1.846, 1.884, 1.922, 1.960, 1.998, 2.037,
    2.075, 2.113, 2.151, 2.190, 2.228, 2.266, 2.304, 2.342,
    2.381, 2.419, 2.457, 2.495, 2.534, 2.572, 2.610, 2.648,
    2.686, 2.724, 2.763, 2.801, 2.839, 2.877, 2.915, 2.954,
    2.992, 2.998, 2.999, 3.000
};

double cell_voltage_lut[] = {
    4.952, 5.048, 5.124, 5.212, 5.294, 5.364, 5.438, 5.508,
    5.592, 5.664, 5.738, 5.808, 5.874, 5.938, 6.002, 6.064,
    6.132, 6.196, 6.260, 6.328, 6.394, 6.460, 6.526, 6.586,
    6.642, 6.694, 6.744, 6.794, 6.832, 6.856, 6.878, 6.898,
    6.920, 6.946, 6.982, 7.018, 7.054, 7.084, 7.112, 7.140,
    7.166, 7.188, 7.212, 7.234, 7.256, 7.280, 7.304, 7.328,
    7.354, 7.378, 7.404, 7.428, 7.454, 7.476, 7.500, 7.522,
    7.546, 7.568, 7.590, 7.614, 7.636, 7.662, 7.686, 7.712,
    7.736, 7.758, 7.782, 7.808, 7.836, 7.866, 7.898, 7.928,
    7.960, 7.988, 8.014, 8.038, 8.056, 8.068, 8.076, 8.082,
    8.088, 8.096, 8.104, 8.112, 8.124, 8.142, 8.166, 8.204,
    8.226, 8.272, 8.330, 8.400
};

double Measure_Cell_Voltage(void){
	//select the correct a/d channel
	uint32_t adc_value = 0;

	for(int i = 0;i < 10;i++){
		HAL_ADC_Start(&hadc4);
		HAL_ADC_PollForConversion(&hadc4, 1);

		adc_value = adc_value + HAL_ADC_GetValue(&hadc4);
		HAL_ADC_Stop(&hadc4);
	}

	adc_value = adc_value / 10;

	return ((double)adc_value/AD_12BIT_RES*AD_REF_VOLTAGE)/CELL_VOLTAGE_DIVIDER;

}
double Find_Capacity(double voltage){
	int table_size = sizeof(cell_voltage_lut) / sizeof(cell_voltage_lut[0]);

	// If the voltage is out of range
	if (voltage > cell_voltage_lut[table_size - 1]) {
		return remaining_capacity_lut[table_size - 1];
	}
	if (voltage < cell_voltage_lut[0]) {
	    return remaining_capacity_lut[0];
	}

	// Find the interval where the voltage fits
	for (int i = 0; i < table_size - 1; i++) {
		if (voltage <= cell_voltage_lut[i + 1] && voltage >= cell_voltage_lut[i]) {
			// Linear interpolation
			double slope = (remaining_capacity_lut[i + 1] - remaining_capacity_lut[i]) / (cell_voltage_lut[i + 1] - cell_voltage_lut[i]);
			return remaining_capacity_lut[i] + slope * (voltage - cell_voltage_lut[i]);
		}
	}

	// Default return in case of error (should never reach here)
	return -1.0;
}

uint8_t CalculateSOC(void){
	double soc = Find_Capacity(Measure_Cell_Voltage())/CELL_CAPACITY;
	return (uint8_t)(100*soc);
}

uint8_t IsCharging(void){
	//not charging
	if (HAL_GPIO_ReadPin(CHARGE_DETECTION_GPIO_Port, CHARGE_DETECTION_Pin) == 1){
		return 0;
	}
	//charging
	else return 1;
}

void SetDetectorVoltage(uint16_t det_voltage_mv){
	uint16_t xref =  (det_voltage_mv+OFFSET)*AD_12BIT_RES/(GAIN*GAIN_COMP*AREF);
	HAL_DAC_Start(&hdac1, DAC_CHANNEL_1);
	HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1,DAC_ALIGN_12B_R,xref);
}

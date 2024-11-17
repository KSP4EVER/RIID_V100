/*
 * application.h
 *
 *  Created on: Nov 14, 2024
 *      Author: Misi
 */

#ifndef INC_APPLICATION_H_
#define INC_APPLICATION_H_

#include "main.h"

#define SPECTRUM_SIZE 4096
#define PEAK_POSITION 700   // Approximate position for the peak in the array
#define PEAK_WIDTH 30       // Width of the peak
#define COMPTON_EDGE 550    // Approximate position for the Compton edge
#define BACKGROUND_LEVEL 5  // Background noise level


void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin);
void delay_us (uint16_t us);
void updateCPS();
void updateCPM();


//functions for simulation purpose
double gaussian(int x, int mean, double std_dev);
void generate_spectrum(uint32_t*, uint32_t);

#endif /* INC_APPLICATION_H_ */

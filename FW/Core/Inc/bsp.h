/*
 * bsp.h
 *
 *  Created on: Nov 12, 2024
 *      Author: Misi
 */

#ifndef INC_BSP_H_
#define INC_BSP_H_

#include "main.h"


#define CELL_CAPACITY 3.0
#define AD_REF_VOLTAGE 3.3
#define AD_12BIT_RES 4096
#define CELL_VOLTAGE_DIVIDER 0.393

#define AREF 3300
#define GAIN 11
#define GAIN_COMP 1.0
#define OFFSET 100

extern ADC_HandleTypeDef hadc4;
extern DAC_HandleTypeDef hdac1;



double Measure_Cell_Voltage(void);
double Find_Capacity(double);
uint8_t CalculateSOC(void);
uint8_t IsCharging(void);

void SetDetectorVoltage(uint16_t);

#endif /* INC_BSP_H_ */

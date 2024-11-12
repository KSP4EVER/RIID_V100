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

extern ADC_HandleTypeDef hadc4;



double Measure_Cell_Voltage(void);
double Find_Capacity(double);
uint8_t CalculateSOC(void);
uint8_t IsCharging(void);


#endif /* INC_BSP_H_ */

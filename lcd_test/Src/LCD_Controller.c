/*
 * LCD_Controller.c
 *
 *  Created on: Apr 15, 2024
 *      Author: Szabo Mihaly
 */

#include "LCD_Controller.h"

#define FMC_BANK1_REG ((uint16_t*)  0x60000000) //reg addr for A0
#define FMC_BANK1_DATA ((uint16_t*) 0x60000002)

void LCD_IO_Init(void)
{
	HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_RESET);
	HAL_Delay(50);
	HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_SET);
	HAL_Delay(50);
}

void LCD_IO_WriteReg(uint8_t Reg)
{
	*FMC_BANK1_REG = Reg;
}

void LCD_IO_WriteData(uint16_t RegValue)
{
	*FMC_BANK1_DATA = RegValue;
}

uint16_t LCD_IO_ReadData(void)
{
	return *FMC_BANK1_DATA;
}

void LCD_IO_WriteMultipleData(uint16_t *pData, uint32_t Size)
{
	for(uint32_t i = 0; i < Size; i++)
	{
		LCD_IO_WriteData(pData[i]);
	}
}

void LCD_IO_Delay(uint32_t delay)
{
	HAL_Delay(delay);
}

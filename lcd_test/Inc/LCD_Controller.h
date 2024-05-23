/*
 * LCD_Controller.h
 *
 *  Created on: Apr 15, 2024
 *      Author: Szabo Mihaly
 */

#ifndef INC_LCD_CONTROLLER_H_
#define INC_LCD_CONTROLLER_H_

#include "main.h"

extern void     LCD_IO_Init(void);
extern void     LCD_IO_WriteMultipleData(uint16_t *pData, uint32_t Size);
extern void     LCD_IO_WriteReg(uint8_t Reg);
extern void     LCD_IO_WriteData(uint16_t RegValue);
extern uint16_t LCD_IO_ReadData(void);
extern void     LCD_IO_Delay(uint32_t delay);

#endif /* INC_LCD_CONTROLLER_H_ */

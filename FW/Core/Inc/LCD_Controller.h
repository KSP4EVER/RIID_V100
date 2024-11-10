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



/*Copy this file as "lv_port_disp.h" and set this value to "1" to enable content*/
#if 1

#ifndef LV_PORT_DISP_TEMPL_H
#define LV_PORT_DISP_TEMPL_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
/* Initialize low level display driver */
void lv_port_disp_init(void);

/* Enable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_enable_update(void);

/* Disable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_disable_update(void);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_PORT_DISP_TEMPL_H*/

#endif /*Disable/Enable content*/



#endif /* INC_LCD_CONTROLLER_H_ */

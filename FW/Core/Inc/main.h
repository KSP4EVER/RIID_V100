/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BUTTON_3_Pin GPIO_PIN_2
#define BUTTON_3_GPIO_Port GPIOE
#define BUTTON_2_Pin GPIO_PIN_3
#define BUTTON_2_GPIO_Port GPIOE
#define BUTTON_1_Pin GPIO_PIN_4
#define BUTTON_1_GPIO_Port GPIOE
#define BUTTON_0_Pin GPIO_PIN_5
#define BUTTON_0_GPIO_Port GPIOE
#define V_DET_TOOGLE_Pin GPIO_PIN_6
#define V_DET_TOOGLE_GPIO_Port GPIOE
#define TRESHHOLD_IRQ_Pin GPIO_PIN_0
#define TRESHHOLD_IRQ_GPIO_Port GPIOA
#define PEAK_DET_RST_Pin GPIO_PIN_2
#define PEAK_DET_RST_GPIO_Port GPIOA
#define BUTTON_7_Pin GPIO_PIN_0
#define BUTTON_7_GPIO_Port GPIOB
#define BUTTON_6_Pin GPIO_PIN_1
#define BUTTON_6_GPIO_Port GPIOB
#define BUTTON_5_Pin GPIO_PIN_2
#define BUTTON_5_GPIO_Port GPIOB
#define LCD_TE_Pin GPIO_PIN_12
#define LCD_TE_GPIO_Port GPIOD
#define SD_DETECT_Pin GPIO_PIN_3
#define SD_DETECT_GPIO_Port GPIOD
#define ON_OFF_INT_Pin GPIO_PIN_6
#define ON_OFF_INT_GPIO_Port GPIOD
#define BUTTON_4_Pin GPIO_PIN_3
#define BUTTON_4_GPIO_Port GPIOB
#define BLE_RST_Pin GPIO_PIN_9
#define BLE_RST_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

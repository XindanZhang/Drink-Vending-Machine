/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "myiic.h"
#include "VL618.h"
#include "bsp_timer.h"

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
#define L0_Pin GPIO_PIN_4
#define L0_GPIO_Port GPIOA
#define L1_Pin GPIO_PIN_5
#define L1_GPIO_Port GPIOA
#define J1_Pin GPIO_PIN_6
#define J1_GPIO_Port GPIOA
#define J2_Pin GPIO_PIN_7
#define J2_GPIO_Port GPIOA
#define J4_Pin GPIO_PIN_4
#define J4_GPIO_Port GPIOC
#define J5_Pin GPIO_PIN_5
#define J5_GPIO_Port GPIOC
#define J3_Pin GPIO_PIN_0
#define J3_GPIO_Port GPIOB
#define VL6180X_SCL_Pin GPIO_PIN_11
#define VL6180X_SCL_GPIO_Port GPIOA
#define VL6180X_SDA_Pin GPIO_PIN_12
#define VL6180X_SDA_GPIO_Port GPIOA
#define TCS_SDA_Pin GPIO_PIN_7
#define TCS_SDA_GPIO_Port GPIOB
#define TCS_SCL_Pin GPIO_PIN_8
#define TCS_SCL_GPIO_Port GPIOB
void   MX_I2C1_Init(void);
void   MX_USART1_UART_Init(void);
void   MX_USART2_UART_Init(void);
void   MX_TIM2_Init(void);
/* USER CODE BEGIN Private defines */

#define BSP_Printf		printf
/* 开关全局中断的宏 */
#define ENABLE_INT()	__set_PRIMASK(0)	/* 使能全局中断 */
#define DISABLE_INT()	__set_PRIMASK(1)	/* 禁止全局中断 */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

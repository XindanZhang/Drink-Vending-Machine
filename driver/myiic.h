#ifndef __MYIIC_H
#define __MYIIC_H
//#include "sys.h"
#include <stdint.h>
#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio.h"
  	   		   
#define VL6180X_SDA_PIN_NUM       11
#define VL6180X_SDA_PIN           GPIO_PIN_11
#define VL6180X_SDA_GPIO          GPIOA
#define VL6180X_SCL_PIN           GPIO_PIN_12
#define VL6180X_SCL_GPIO          GPIOA

/******************************************************************************/
#define VL6180X_SDA_DIR_IN()     {VL6180X_SDA_GPIO->MODER&=~(3<<(VL6180X_SDA_PIN_NUM*2));VL6180X_SDA_GPIO->MODER|=0<<VL6180X_SDA_PIN_NUM*2;}//输入模式

#define VL6180X_SDA_DIR_OUT()    {VL6180X_SDA_GPIO->MODER&=~(3<<(VL6180X_SDA_PIN_NUM*2));VL6180X_SDA_GPIO->MODER|=1<<VL6180X_SDA_PIN_NUM*2;}//输出模式

#define VL6180X_SDA_READ          HAL_GPIO_ReadPin(VL6180X_SDA_GPIO, VL6180X_SDA_PIN)
#define VL6180X_SDA_SET           HAL_GPIO_WritePin(VL6180X_SDA_GPIO, VL6180X_SDA_PIN, GPIO_PIN_SET)
#define VL6180X_SDA_RESET         HAL_GPIO_WritePin(VL6180X_SDA_GPIO, VL6180X_SDA_PIN, GPIO_PIN_RESET)
#define VL6180X_SCL_SET           HAL_GPIO_WritePin(VL6180X_SCL_GPIO, VL6180X_SCL_PIN, GPIO_PIN_SET)
#define VL6180X_SCL_RESET         HAL_GPIO_WritePin(VL6180X_SCL_GPIO, VL6180X_SCL_PIN, GPIO_PIN_RESET)

//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(uint8_t txd);			//IIC发送一个字节
uint8_t IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
uint8_t IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号
  
#endif

















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
#define VL6180X_SDA_DIR_IN()     {VL6180X_SDA_GPIO->MODER&=~(3<<(VL6180X_SDA_PIN_NUM*2));VL6180X_SDA_GPIO->MODER|=0<<VL6180X_SDA_PIN_NUM*2;}//����ģʽ

#define VL6180X_SDA_DIR_OUT()    {VL6180X_SDA_GPIO->MODER&=~(3<<(VL6180X_SDA_PIN_NUM*2));VL6180X_SDA_GPIO->MODER|=1<<VL6180X_SDA_PIN_NUM*2;}//���ģʽ

#define VL6180X_SDA_READ          HAL_GPIO_ReadPin(VL6180X_SDA_GPIO, VL6180X_SDA_PIN)
#define VL6180X_SDA_SET           HAL_GPIO_WritePin(VL6180X_SDA_GPIO, VL6180X_SDA_PIN, GPIO_PIN_SET)
#define VL6180X_SDA_RESET         HAL_GPIO_WritePin(VL6180X_SDA_GPIO, VL6180X_SDA_PIN, GPIO_PIN_RESET)
#define VL6180X_SCL_SET           HAL_GPIO_WritePin(VL6180X_SCL_GPIO, VL6180X_SCL_PIN, GPIO_PIN_SET)
#define VL6180X_SCL_RESET         HAL_GPIO_WritePin(VL6180X_SCL_GPIO, VL6180X_SCL_PIN, GPIO_PIN_RESET)

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(uint8_t txd);			//IIC����һ���ֽ�
uint8_t IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
uint8_t IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�
  
#endif

















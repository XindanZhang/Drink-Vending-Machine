#ifndef __VL618_H
#define __VL618_H
#include "main.h"

uint8_t VL6180X_Init(void);
uint8_t VL6180X_WriteByte(uint16_t reg,uint8_t data);
uint8_t VL6180X_ReadByte(uint16_t reg);
uint8_t VL6180X_Read_ID(void);
uint8_t VL6180X_Read_Range(void);


#endif

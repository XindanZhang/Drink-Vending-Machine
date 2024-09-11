#include "VL618.h"
#include "myiic.h"

#define	VL6180X_DEFAULT_ID						0xB4
//#define I2C_DEBUG
#define VL6180X_DEFAULT_I2C_ADDR 				0x29  ///< The fixed I2C addres
/*------------------VL6180X内部寄存器------------------*/
///! Device model identification number
#define VL6180X_REG_IDENTIFICATION_MODEL_ID    0x000
///! Interrupt configuration
#define VL6180X_REG_SYSTEM_INTERRUPT_CONFIG    0x014
///! Interrupt clear bits
#define VL6180X_REG_SYSTEM_INTERRUPT_CLEAR     0x015
///! Fresh out of reset bit
#define VL6180X_REG_SYSTEM_FRESH_OUT_OF_RESET  0x016
///! Trigger Ranging
#define VL6180X_REG_SYSRANGE_START             0x018
///! Trigger Lux Reading
#define VL6180X_REG_SYSALS_START               0x038
///! Lux reading gain
#define VL6180X_REG_SYSALS_ANALOGUE_GAIN       0x03F
///! Integration period for ALS mode, high byte
#define VL6180X_REG_SYSALS_INTEGRATION_PERIOD_HI  0x040
///! Integration period for ALS mode, low byte
#define VL6180X_REG_SYSALS_INTEGRATION_PERIOD_LO  0x041
///! Specific error codes
#define VL6180X_REG_RESULT_RANGE_STATUS        0x04d
///! Interrupt status
#define VL6180X_REG_RESULT_INTERRUPT_STATUS_GPIO       0x04f
///! Light reading value
#define VL6180X_REG_RESULT_ALS_VAL             0x050
///! Ranging reading value
#define VL6180X_REG_RESULT_RANGE_VAL           0x062

#define VL6180X_ALS_GAIN_1         0x06  ///< 1x gain
#define VL6180X_ALS_GAIN_1_25      0x05  ///< 1.25x gain
#define VL6180X_ALS_GAIN_1_67      0x04  ///< 1.67x gain
#define VL6180X_ALS_GAIN_2_5       0x03  ///< 2.5x gain
#define VL6180X_ALS_GAIN_5         0x02  ///< 5x gain
#define VL6180X_ALS_GAIN_10        0x01  ///< 10x gain
#define VL6180X_ALS_GAIN_20        0x00  ///< 20x gain
#define VL6180X_ALS_GAIN_40        0x07  ///< 40x gain

#define VL6180X_ERROR_NONE         0   ///< Success!
#define VL6180X_ERROR_SYSERR_1     1   ///< System error
#define VL6180X_ERROR_SYSERR_5     5   ///< Sysem error
#define VL6180X_ERROR_ECEFAIL      6   ///< Early convergence estimate fail
#define VL6180X_ERROR_NOCONVERGE   7   ///< No target detected
#define VL6180X_ERROR_RANGEIGNORE  8   ///< Ignore threshold check failed
#define VL6180X_ERROR_SNR          11  ///< Ambient conditions too high
#define VL6180X_ERROR_RAWUFLOW     12  ///< Raw range algo underflow
#define VL6180X_ERROR_RAWOFLOW     13  ///< Raw range algo overflow
#define VL6180X_ERROR_RANGEUFLOW   14  ///< Raw range algo underflow
#define VL6180X_ERROR_RANGEOFLOW   15  ///< Raw range algo overflow


//写	reg寄存器 data数据
uint8_t VL6180X_WriteByte(uint16_t reg,uint8_t data)
{
	uint8_t Index_H = (uint8_t)(reg >> 8);
	uint8_t Index_L = (uint8_t)(reg & 0xFF);
	
	IIC_Start();
	IIC_Send_Byte((VL6180X_DEFAULT_I2C_ADDR<<1)|0);
	if(IIC_Wait_Ack())	//等待应答
	{
		IIC_Stop();	
		return 1;		
	}
	IIC_Send_Byte(Index_H);
	IIC_Wait_Ack();	//等待ACK
	IIC_Send_Byte(Index_L);
	IIC_Wait_Ack();	//等待ACK
	IIC_Send_Byte(data);
	if(IIC_Wait_Ack())	//等待ACK
	{
		IIC_Stop();	 
		return 1;		 
	}
	IIC_Stop();
	return 0;	
}

//VL6180X读取8位数据
uint8_t VL6180X_ReadByte(uint16_t reg)
{
	uint8_t res;
	uint8_t Index_H = (uint8_t)(reg >> 8);
	uint8_t Index_L = (uint8_t)(reg & 0xff);
    IIC_Start(); 
	IIC_Send_Byte((VL6180X_DEFAULT_I2C_ADDR<<1)|0);//发送器件地址+写命令	
	IIC_Wait_Ack();		//等待应答 
    IIC_Send_Byte(Index_H);	//写寄存器地址
    IIC_Wait_Ack();		//等待应答
	IIC_Send_Byte(Index_L);	//写寄存器地址
	IIC_Wait_Ack();	
	
    IIC_Start();
	IIC_Send_Byte((VL6180X_DEFAULT_I2C_ADDR<<1)|1);//发送器件地址+读命令	
    IIC_Wait_Ack();		//等待应答 
	res=IIC_Read_Byte(0);//读取数据,发送nACK 
    IIC_Stop();			//产生一个停止条件 
	return res;
}


uint8_t VL6180X_Read_ID(void)
{
	return VL6180X_ReadByte(VL6180X_REG_IDENTIFICATION_MODEL_ID);
}

uint8_t VL6180X_Init(void)
{
	if(VL6180X_Read_ID() == VL6180X_DEFAULT_ID)
	{	
		VL6180X_WriteByte(0x0207, 0x01);
		VL6180X_WriteByte(0x0208, 0x01);
		VL6180X_WriteByte(0x0096, 0x00);
		VL6180X_WriteByte(0x0097, 0xfd);
		VL6180X_WriteByte(0x00e3, 0x00);
		VL6180X_WriteByte(0x00e4, 0x04);
		VL6180X_WriteByte(0x00e5, 0x02);
		VL6180X_WriteByte(0x00e6, 0x01);
		VL6180X_WriteByte(0x00e7, 0x03);
		VL6180X_WriteByte(0x00f5, 0x02);
		VL6180X_WriteByte(0x00d9, 0x05);
		VL6180X_WriteByte(0x00db, 0xce);
		VL6180X_WriteByte(0x00dc, 0x03);
		VL6180X_WriteByte(0x00dd, 0xf8);
		VL6180X_WriteByte(0x009f, 0x00);
		VL6180X_WriteByte(0x00a3, 0x3c);
		VL6180X_WriteByte(0x00b7, 0x00);
		VL6180X_WriteByte(0x00bb, 0x3c);
		VL6180X_WriteByte(0x00b2, 0x09);
		VL6180X_WriteByte(0x00ca, 0x09);
		VL6180X_WriteByte(0x0198, 0x01);
		VL6180X_WriteByte(0x01b0, 0x17);
		VL6180X_WriteByte(0x01ad, 0x00);
		VL6180X_WriteByte(0x00ff, 0x05);
		VL6180X_WriteByte(0x0100, 0x05);
		VL6180X_WriteByte(0x0199, 0x05);
		VL6180X_WriteByte(0x01a6, 0x1b);
		VL6180X_WriteByte(0x01ac, 0x3e);
		VL6180X_WriteByte(0x01a7, 0x1f);
		VL6180X_WriteByte(0x0030, 0x00);
		
		// Recommended : Public registers - See data sheet for more detail
		VL6180X_WriteByte(0x0011, 0x10);       // Enables polling for 'New Sample ready'
									// when measurement completes
		VL6180X_WriteByte(0x010a, 0x30);       // Set the averaging sample period
									// (compromise between lower noise and
									// increased execution time)
		VL6180X_WriteByte(0x003f, 0x46);       // Sets the light and dark gain (upper
									// nibble). Dark gain should not be
									// changed. !上半字节要写入0x4	默认增益是1.0
		VL6180X_WriteByte(0x0031, 0xFF);       // sets the # of range measurements after
									// which auto calibration of system is
									// performed
		VL6180X_WriteByte(0x0040, 0x63);       // Set ALS integration time to 100ms
		VL6180X_WriteByte(0x002e, 0x01);       // perform a single temperature calibration
									// of the ranging sensor

		// Optional: Public registers - See data sheet for more detail
		VL6180X_WriteByte(0x001b, 0x09);    //测量间隔	轮询模式
									// period to 100ms	每步10ms->0-10ms
		VL6180X_WriteByte(0x003e, 0x31);      //测量周期	ALS模式
									// to 500ms		
		VL6180X_WriteByte(0x0014, 0x24);       // Configures interrupt on 'New Sample
									// Ready threshold event'
		return 0;
	}
	else return 1;
}


//单位毫米
uint8_t VL6180X_Read_Range(void)
{
	uint8_t range = 0;
	//开启传输
	while(!(VL6180X_ReadByte(VL6180X_REG_RESULT_RANGE_STATUS) & 0x01));
	VL6180X_WriteByte(VL6180X_REG_SYSRANGE_START,0x01);	//单次触发模式
	//等待新样本就绪阈值事件(New Sample Ready threshold event)
	while(!(VL6180X_ReadByte(VL6180X_REG_RESULT_INTERRUPT_STATUS_GPIO) & 0x04));
	range = VL6180X_ReadByte(VL6180X_REG_RESULT_RANGE_VAL);
	//获取完数据，清楚中断位
	VL6180X_WriteByte(VL6180X_REG_SYSTEM_INTERRUPT_CLEAR,0x07);	//0111b 清除了三种中断标志
	return range;
}




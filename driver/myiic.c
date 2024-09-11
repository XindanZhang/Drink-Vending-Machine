#include "myiic.h"
#include "bsp_timer.h"

void IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure; 
	__HAL_RCC_GPIOA_CLK_ENABLE();   //使能GPIOI时钟
	
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_Initure.Pull = GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed = GPIO_SPEED_FAST;     //快速 
	
    GPIO_Initure.Pin = VL6180X_SDA_PIN;
	HAL_GPIO_Init(VL6180X_SDA_GPIO, &GPIO_Initure);
	GPIO_Initure.Pin = VL6180X_SCL_PIN;
	HAL_GPIO_Init(VL6180X_SCL_GPIO, &GPIO_Initure);
	
	VL6180X_SDA_SET;
	VL6180X_SCL_SET;
	
	HAL_Delay(10);
}

//产生I2C起始信号
void IIC_Start()
{
	VL6180X_SDA_DIR_OUT();//sda线输出
	VL6180X_SDA_SET;
	VL6180X_SCL_SET;
	bsp_DelayUS(4);
	VL6180X_SDA_RESET;//START:when CLK is high,DATA change form high to low 
	bsp_DelayUS(4);
	VL6180X_SCL_RESET;//钳住I2C总线，准备发送或接收数据 
}

//产生I2C停止信号
void IIC_Stop()
{
	VL6180X_SDA_DIR_OUT();//sda线输出
	VL6180X_SCL_RESET;
	VL6180X_SDA_RESET;//STOP:when CLK is high DATA change form low to high
	bsp_DelayUS(4);
	VL6180X_SCL_SET;
	VL6180X_SDA_SET;//发送I2C总线结束信号
	bsp_DelayUS(4);							   	
}

//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
uint8_t IIC_Wait_Ack()
{
	uint8_t timeOut = 0;
	
	VL6180X_SDA_DIR_IN();//SDA设置为输入  
	VL6180X_SDA_SET; bsp_DelayUS(1);
	VL6180X_SCL_SET; bsp_DelayUS(1);
	while(VL6180X_SDA_READ)
	{
		timeOut++;
		if(timeOut > 250)
		{
			IIC_Stop();
			return 1;
		}
	}
	VL6180X_SCL_RESET;//时钟输出0
			
	return 0;	
} 

//产生ACK应答
void IIC_Ack()
{
	VL6180X_SCL_RESET;
	VL6180X_SDA_DIR_OUT();//sda线输出
	VL6180X_SDA_RESET;
	bsp_DelayUS(2);
	VL6180X_SCL_SET;
	bsp_DelayUS(2);
	VL6180X_SCL_RESET;
}

//不产生ACK应答		    
void IIC_NAck()
{
	VL6180X_SCL_RESET;
	VL6180X_SDA_DIR_OUT();//sda线输出
	VL6180X_SDA_SET;
	bsp_DelayUS(2);
	VL6180X_SCL_SET;
	bsp_DelayUS(2);
	VL6180X_SCL_RESET;
}	

//I2C发送一个字节		  
void IIC_Send_Byte(uint8_t byte)
{
	uint8_t i = 0;
	
	VL6180X_SDA_DIR_OUT();//sda线输出
	VL6180X_SCL_RESET;//拉低时钟开始数据传输
	for(i = 0; i < 8; i++)
	{
		((byte & 0x80) >> 7) == 0x01 ? VL6180X_SDA_SET : VL6180X_SDA_RESET;
		byte <<= 1;
		bsp_DelayUS(2);
		VL6180X_SCL_SET;
		bsp_DelayUS(2);
		VL6180X_SCL_RESET;
		bsp_DelayUS(2);
	} 
} 

//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
uint8_t IIC_Read_Byte(uint8_t ack)
{
	uint8_t i,receive = 0;
	
	VL6180X_SDA_DIR_IN();
	for(i = 0; i < 8; i++)
	{
		VL6180X_SCL_RESET;
		bsp_DelayUS(2);
		VL6180X_SCL_SET;
		receive <<= 1;
		if(VL6180X_SDA_READ) receive++;
		bsp_DelayUS(1);
	}
	if (!ack) IIC_NAck();//发送nACK
	else IIC_Ack(); //发送ACK 
	
	return receive;
}






















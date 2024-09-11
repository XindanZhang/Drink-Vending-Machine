#include "myiic.h"
#include "bsp_timer.h"

void IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure; 
	__HAL_RCC_GPIOA_CLK_ENABLE();   //ʹ��GPIOIʱ��
	
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull = GPIO_PULLUP;          //����
    GPIO_Initure.Speed = GPIO_SPEED_FAST;     //���� 
	
    GPIO_Initure.Pin = VL6180X_SDA_PIN;
	HAL_GPIO_Init(VL6180X_SDA_GPIO, &GPIO_Initure);
	GPIO_Initure.Pin = VL6180X_SCL_PIN;
	HAL_GPIO_Init(VL6180X_SCL_GPIO, &GPIO_Initure);
	
	VL6180X_SDA_SET;
	VL6180X_SCL_SET;
	
	HAL_Delay(10);
}

//����I2C��ʼ�ź�
void IIC_Start()
{
	VL6180X_SDA_DIR_OUT();//sda�����
	VL6180X_SDA_SET;
	VL6180X_SCL_SET;
	bsp_DelayUS(4);
	VL6180X_SDA_RESET;//START:when CLK is high,DATA change form high to low 
	bsp_DelayUS(4);
	VL6180X_SCL_RESET;//ǯסI2C���ߣ�׼�����ͻ�������� 
}

//����I2Cֹͣ�ź�
void IIC_Stop()
{
	VL6180X_SDA_DIR_OUT();//sda�����
	VL6180X_SCL_RESET;
	VL6180X_SDA_RESET;//STOP:when CLK is high DATA change form low to high
	bsp_DelayUS(4);
	VL6180X_SCL_SET;
	VL6180X_SDA_SET;//����I2C���߽����ź�
	bsp_DelayUS(4);							   	
}

//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
uint8_t IIC_Wait_Ack()
{
	uint8_t timeOut = 0;
	
	VL6180X_SDA_DIR_IN();//SDA����Ϊ����  
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
	VL6180X_SCL_RESET;//ʱ�����0
			
	return 0;	
} 

//����ACKӦ��
void IIC_Ack()
{
	VL6180X_SCL_RESET;
	VL6180X_SDA_DIR_OUT();//sda�����
	VL6180X_SDA_RESET;
	bsp_DelayUS(2);
	VL6180X_SCL_SET;
	bsp_DelayUS(2);
	VL6180X_SCL_RESET;
}

//������ACKӦ��		    
void IIC_NAck()
{
	VL6180X_SCL_RESET;
	VL6180X_SDA_DIR_OUT();//sda�����
	VL6180X_SDA_SET;
	bsp_DelayUS(2);
	VL6180X_SCL_SET;
	bsp_DelayUS(2);
	VL6180X_SCL_RESET;
}	

//I2C����һ���ֽ�		  
void IIC_Send_Byte(uint8_t byte)
{
	uint8_t i = 0;
	
	VL6180X_SDA_DIR_OUT();//sda�����
	VL6180X_SCL_RESET;//����ʱ�ӿ�ʼ���ݴ���
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

//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
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
	if (!ack) IIC_NAck();//����nACK
	else IIC_Ack(); //����ACK 
	
	return receive;
}






















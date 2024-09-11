#include "tcs34725.h"
#include "bsp_timer.h"
//TCS34725 I2C��ʼ��
void TCS34725_I2C_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure; 
	__HAL_RCC_GPIOB_CLK_ENABLE();   //ʹ��GPIOIʱ��
	
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull = GPIO_PULLUP;          //����
    GPIO_Initure.Speed = GPIO_SPEED_FAST;     //���� 
	
    GPIO_Initure.Pin = TCS_SDA_PIN;
	HAL_GPIO_Init(TCS_SDA_GPIO, &GPIO_Initure);
	GPIO_Initure.Pin = TCS_SCL_PIN;
	HAL_GPIO_Init(TCS_SCL_GPIO, &GPIO_Initure);
	
	TCS_SDA_SET;
	TCS_SCL_SET;
	
	HAL_Delay(10);
}

//����I2C��ʼ�ź�
void TCS34725_I2C_Start()
{
	TCS_SDA_DIR_OUT();//sda�����
	TCS_SDA_SET;
	TCS_SCL_SET;
	bsp_DelayUS(4);
	TCS_SDA_RESET;//START:when CLK is high,DATA change form high to low 
	bsp_DelayUS(4);
	TCS_SCL_RESET;//ǯסI2C���ߣ�׼�����ͻ�������� 
}

//����I2Cֹͣ�ź�
void TCS34725_I2C_Stop()
{
	TCS_SDA_DIR_OUT();//sda�����
	TCS_SCL_RESET;
	TCS_SDA_RESET;//STOP:when CLK is high DATA change form low to high
	bsp_DelayUS(4);
	TCS_SCL_SET;
	TCS_SDA_SET;//����I2C���߽����ź�
	bsp_DelayUS(4);							   	
}

//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
uint8_t TCS34725_I2C_Wait_ACK()
{
	uint8_t timeOut = 0;
	
	TCS_SDA_DIR_IN();//SDA����Ϊ����  
	TCS_SDA_SET; bsp_DelayUS(1);
	TCS_SCL_SET; bsp_DelayUS(1);
	while(TCS_SDA_READ)
	{
		timeOut++;
		if(timeOut > 250)
		{
			TCS34725_I2C_Stop();
			return 1;
		}
	}
	TCS_SCL_RESET;//ʱ�����0
			
	return 0;	
} 

//����ACKӦ��
void TCS34725_I2C_ACK()
{
	TCS_SCL_RESET;
	TCS_SDA_DIR_OUT();//sda�����
	TCS_SDA_RESET;
	bsp_DelayUS(2);
	TCS_SCL_SET;
	bsp_DelayUS(2);
	TCS_SCL_RESET;
}

//������ACKӦ��		    
void TCS34725_I2C_NACK()
{
	TCS_SCL_RESET;
	TCS_SDA_DIR_OUT();//sda�����
	TCS_SDA_SET;
	bsp_DelayUS(2);
	TCS_SCL_SET;
	bsp_DelayUS(2);
	TCS_SCL_RESET;
}	

//I2C����һ���ֽ�		  
void TCS34725_I2C_Send_Byte(uint8_t byte)
{
	uint8_t i = 0;
	
	TCS_SDA_DIR_OUT();//sda�����
	TCS_SCL_RESET;//����ʱ�ӿ�ʼ���ݴ���
	for(i = 0; i < 8; i++)
	{
		((byte & 0x80) >> 7) == 0x01 ? TCS_SDA_SET : TCS_SDA_RESET;
		byte <<= 1;
		bsp_DelayUS(2);
		TCS_SCL_SET;
		bsp_DelayUS(2);
		TCS_SCL_RESET;
		bsp_DelayUS(2);
	} 
} 

//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
uint8_t TCS34725_I2C_Read_Byte(uint8_t ack)
{
	uint8_t i,receive = 0;
	
	TCS_SDA_DIR_IN();
	for(i = 0; i < 8; i++)
	{
		TCS_SCL_RESET;
		bsp_DelayUS(2);
		TCS_SCL_SET;
		receive <<= 1;
		if(TCS_SDA_READ) receive++;
		bsp_DelayUS(1);
	}
	if (!ack) TCS34725_I2C_NACK();//����nACK
	else TCS34725_I2C_ACK(); //����ACK 
	
	return receive;
}
/***************************************************************************//**
 * @brief Writes data to a slave device.
 *
 * @param slaveAddress - Adress of the slave device.
 * @param dataBuffer - Pointer to a buffer storing the transmission data.
 * @param bytesNumber - Number of bytes to write.
 * @param stopBit - Stop condition control.
 *                  Example: 0 - A stop condition will not be sent;
 *                           1 - A stop condition will be sent.
*******************************************************************************/
void TCS34725_I2C_Write(uint8_t slaveAddress, 
						uint8_t* dataBuffer,
						uint8_t bytesNumber, 
						uint8_t stopBit)
{
	unsigned char i = 0;
	
	TCS34725_I2C_Start();
	TCS34725_I2C_Send_Byte((slaveAddress << 1) | 0x00);	   //���ʹӻ���ַд����
	TCS34725_I2C_Wait_ACK();
	for(i = 0; i < bytesNumber; i++)
	{
		TCS34725_I2C_Send_Byte(*(dataBuffer + i));
		TCS34725_I2C_Wait_ACK();
	}
	if(stopBit == 1) TCS34725_I2C_Stop();
}

/***************************************************************************//**
 * @brief Reads data from a slave device.
 *
 * @param slaveAddress - Adress of the slave device.
 * @param dataBuffer - Pointer to a buffer that will store the received data.
 * @param bytesNumber - Number of bytes to read.
 * @param stopBit - Stop condition control.
 *                  Example: 0 - A stop condition will not be sent;
 *                           1 - A stop condition will be sent.
*******************************************************************************/
void TCS34725_I2C_Read(uint8_t slaveAddress, 
						uint8_t* dataBuffer, 
						uint8_t bytesNumber, 
						uint8_t stopBit)
{
	unsigned char i = 0;
	
	TCS34725_I2C_Start();
	TCS34725_I2C_Send_Byte((slaveAddress << 1) | 0x01);	   //���ʹӻ���ַ������
	TCS34725_I2C_Wait_ACK();
	for(i = 0; i < bytesNumber; i++)
	{
		if(i == bytesNumber - 1)
		{
			*(dataBuffer + i) = TCS34725_I2C_Read_Byte(0);//��ȡ�����һ���ֽڷ���NACK
		}
		else
		{
			*(dataBuffer + i) = TCS34725_I2C_Read_Byte(1);
		}
	}
	if(stopBit == 1) TCS34725_I2C_Stop();
}

/***************************************************************************//**
 * @brief Writes data into TCS34725 registers, starting from the selected
 *        register address pointer.
 *
 * @param subAddr - The selected register address pointer.
 * @param dataBuffer - Pointer to a buffer storing the transmission data.
 * @param bytesNumber - Number of bytes that will be sent.
 *
 * @return None.
*******************************************************************************/
void TCS34725_Write(unsigned char subAddr, unsigned char* dataBuffer, unsigned char bytesNumber)
{
    unsigned char sendBuffer[10] = {0, };
    unsigned char byte = 0;
    
    sendBuffer[0] = subAddr | TCS34725_COMMAND_BIT;
    for(byte = 1; byte <= bytesNumber; byte++)
    {
        sendBuffer[byte] = dataBuffer[byte - 1];
    }
	TCS34725_I2C_Write(TCS34725_ADDRESS, sendBuffer, bytesNumber + 1, 1);
}

/***************************************************************************//**
 * @brief Reads data from TCS34725 registers, starting from the selected
 *        register address pointer.
 *
 * @param subAddr - The selected register address pointer.
 * @param dataBuffer - Pointer to a buffer that will store the received data.
 * @param bytesNumber - Number of bytes that will be read.
 *
 * @return None.
*******************************************************************************/
void TCS34725_Read(unsigned char subAddr, unsigned char* dataBuffer, unsigned char bytesNumber)
{
	subAddr |= TCS34725_COMMAND_BIT;
	
	TCS34725_I2C_Write(TCS34725_ADDRESS, (unsigned char*)&subAddr, 1, 0);
	TCS34725_I2C_Read(TCS34725_ADDRESS, dataBuffer, bytesNumber, 1);
}
/***************************************************************************//**
 * @brief TCS34725��ʼ��
 *
 * @return ID - ID�Ĵ����е�ֵ
*******************************************************************************/
unsigned char TCS34725_Init(void)
{
    unsigned char status[1] = {0};
	
	TCS34725_I2C_Init(); 
	TCS34725_Read(TCS34725_ID, status, 1);
    return status[0];
}
/***************************************************************************//**
 * @brief TCS34725���û���ʱ��
 *
 * @return None
*******************************************************************************/
void TCS34725_SetIntegrationTime(uint8_t time)
{
	unsigned char cmd = time;
	
	TCS34725_Write(TCS34725_ATIME, &cmd, 1);
}
/***************************************************************************//**
 * @brief TCS34725��������
 *
 * @return None
*******************************************************************************/
void TCS34725_SetGain(uint8_t gain)
{
	unsigned char cmd = gain;
	
	TCS34725_Write(TCS34725_CONTROL, &cmd, 1);
}
/***************************************************************************//**
 * @brief TCS34725���üĴ���
 *
 * @return None
*******************************************************************************/
void TCS34725_Setup(void)
{
	TCS34725_SetIntegrationTime(TCS34725_INTEGRATIONTIME_240MS);
	TCS34725_SetGain(TCS34725_GAIN_4X);
}
/***************************************************************************//**
 * @brief TCS34725ʹ��
 *
 * @return None
*******************************************************************************/
void TCS34725_Enable(void)
{
	unsigned char cmd = TCS34725_ENABLE_PON;
	
	TCS34725_Write(TCS34725_ENABLE, &cmd, 1);
	cmd = TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN;
	TCS34725_Write(TCS34725_ENABLE, &cmd, 1);
	HAL_Delay(3);
}
/***************************************************************************//**
 * @brief TCS34725ʧ��
 *
 * @return None
*******************************************************************************/
void TCS34725_Disable(void)
{
	unsigned char cmd = 0x00;
	
	TCS34725_Read(TCS34725_ENABLE, &cmd, 1);
	cmd = cmd & ~(TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN);
	TCS34725_Write(TCS34725_ENABLE, &cmd, 1);
}
/***************************************************************************//**
 * @brief TCS34725��ȡ����ͨ������
 *
 * @return data - ��ͨ����ת��ֵ
*******************************************************************************/
uint16_t TCS34725_GetChannelData(unsigned char reg)
{
	unsigned char tmp[2] = {0,0};
	uint16_t data = 0;
	
	TCS34725_Read(reg, tmp, 2);
	data = ((uint16_t)tmp[1] << 8) | tmp[0];
	
	return data;
}
/***************************************************************************//**
 * @brief TCS34725��ȡ����ͨ������
 *
 * @return 1 - ת����ɣ����ݿ���
 *   	   0 - ת��δ��ɣ����ݲ�����
*******************************************************************************/
uint8_t TCS34725_GetRawData(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c)
{
	unsigned char status[1] = {0};

	status[0] = TCS34725_STATUS_AVALID;
	
	TCS34725_Read(TCS34725_STATUS, status, 1);
	
	if(status[0] & TCS34725_STATUS_AVALID)
	{
		*c = TCS34725_GetChannelData(TCS34725_CDATAL);	
		*r = TCS34725_GetChannelData(TCS34725_RDATAL);	
		*g = TCS34725_GetChannelData(TCS34725_GDATAL);	
		*b = TCS34725_GetChannelData(TCS34725_BDATAL);
		return 1;
	}
	return 0;
}


/******************************************************************************/
//RGBתHSL
void RGBtoHSL(COLOR_RGBC *Rgb, COLOR_HSL *Hsl)
{
	uint8_t maxVal,minVal,difVal;
	uint8_t r = Rgb->r*100/Rgb->c;   //[0-100]
	uint8_t g = Rgb->g*100/Rgb->c;
	uint8_t b = Rgb->b*100/Rgb->c;
	
	maxVal = max3v(r,g,b);
	minVal = min3v(r,g,b);
	difVal = maxVal-minVal;
	
	//��������
	Hsl->l = (maxVal+minVal)/2;
	
	if(maxVal == minVal)//��r=g=b,�Ҷ�
	{
		Hsl->h = 0; 
		Hsl->s = 0;
	}
	else
	{
		//����ɫ��
		if(maxVal==r)
		{
			if(g>=b)
				Hsl->h = 60*(g-b)/difVal;
			else
				Hsl->h = 60*(g-b)/difVal+360;
		}
		else
			{
				if(maxVal==g)Hsl->h = 60*(b-r)/difVal+120;
				else
					if(maxVal==b)Hsl->h = 60*(r-g)/difVal+240;
			}
		
		//���㱥�Ͷ�
		if(Hsl->l<=50)Hsl->s=difVal*100/(maxVal+minVal);  //[0-100]
		else
			Hsl->s=difVal*100/(200-(maxVal+minVal));
	}
}
/******************************************************************************/


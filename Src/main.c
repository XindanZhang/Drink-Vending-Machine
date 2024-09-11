/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "tcs34725.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
 UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint16_t u16_r;
uint16_t u16_b;
uint16_t u16_g;
uint8_t  range;
COLOR_RGBC rgb;
void zq01(){//ץȡ
	HAL_GPIO_WritePin(GPIOB,J3_Pin,GPIO_PIN_RESET);//�½�
	bsp_DelayMS(500);	
	HAL_GPIO_WritePin(GPIOC,J4_Pin,GPIO_PIN_SET);//ǰ��
	bsp_DelayMS(500);
	HAL_GPIO_WritePin(GPIOC,J5_Pin,GPIO_PIN_SET);//ץȡ
	bsp_DelayMS(1000);	
	HAL_GPIO_WritePin(GPIOC,J4_Pin,GPIO_PIN_RESET);//����
	bsp_DelayMS(500);
	HAL_GPIO_WritePin(GPIOB,J3_Pin,GPIO_PIN_SET);//����
	bsp_DelayMS(500);		
	HAL_GPIO_WritePin(GPIOA,J1_Pin,GPIO_PIN_RESET);//����
	HAL_GPIO_WritePin(GPIOA,J2_Pin,GPIO_PIN_SET);
	bsp_DelayMS(500);	
}
void zq10(){//ץȡ
	HAL_GPIO_WritePin(GPIOB,J3_Pin,GPIO_PIN_RESET);//�½�
	bsp_DelayMS(500);	
	HAL_GPIO_WritePin(GPIOC,J4_Pin,GPIO_PIN_SET);//ǰ��
	bsp_DelayMS(500);
	HAL_GPIO_WritePin(GPIOC,J5_Pin,GPIO_PIN_SET);//ץȡ
	bsp_DelayMS(1000);	
	HAL_GPIO_WritePin(GPIOC,J4_Pin,GPIO_PIN_RESET);//����
	bsp_DelayMS(500);
	HAL_GPIO_WritePin(GPIOB,J3_Pin,GPIO_PIN_SET);//����
	bsp_DelayMS(500);		
	HAL_GPIO_WritePin(GPIOA,J1_Pin,GPIO_PIN_RESET);//����
	HAL_GPIO_WritePin(GPIOA,J2_Pin,GPIO_PIN_SET);
	bsp_DelayMS(500);	
}
void zq11(){//ץȡ
	HAL_GPIO_WritePin(GPIOB,J3_Pin,GPIO_PIN_RESET);//�½�
	bsp_DelayMS(500);	
	HAL_GPIO_WritePin(GPIOC,J4_Pin,GPIO_PIN_SET);//ǰ��
	bsp_DelayMS(500);
	HAL_GPIO_WritePin(GPIOC,J5_Pin,GPIO_PIN_SET);//ץȡ
	bsp_DelayMS(1000);	
	HAL_GPIO_WritePin(GPIOC,J4_Pin,GPIO_PIN_RESET);//����
	bsp_DelayMS(500);
	HAL_GPIO_WritePin(GPIOB,J3_Pin,GPIO_PIN_SET);//����
	bsp_DelayMS(500);		
	HAL_GPIO_WritePin(GPIOA,J1_Pin,GPIO_PIN_RESET);//����
	HAL_GPIO_WritePin(GPIOA,J2_Pin,GPIO_PIN_SET);
	bsp_DelayMS(500);	
}
void zq00()
{
	HAL_GPIO_WritePin(GPIOA,J1_Pin,GPIO_PIN_RESET);//����
	HAL_GPIO_WritePin(GPIOA,J2_Pin,GPIO_PIN_RESET);
	bsp_DelayMS(500);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
	bsp_InitTimer();
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	TCS34725_Init();
	TCS34725_Enable();
	TCS34725_Setup();
	
	IIC_Init();
	while(VL6180X_Init() != 0)	
	{
		printf("VL6180X Error!\r\n");
		bsp_DelayMS(500);
	}
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		char re = '0';
		//������λ���ź�
		HAL_UART_Receive(&huart1,(uint8_t *)&re,(uint16_t)sizeof(re),100);
//		printf("Received:%c\n",re);
		
		//check mode����ά��ģʽ
		if(re=='m')
		{
				//����е��
				HAL_GPIO_WritePin(GPIOB,J3_Pin,GPIO_PIN_RESET);//�½�
				bsp_DelayMS(500);	
				HAL_GPIO_WritePin(GPIOC,J4_Pin,GPIO_PIN_SET);//ǰ��
				bsp_DelayMS(500);
				HAL_GPIO_WritePin(GPIOC,J5_Pin,GPIO_PIN_SET);//ץȡ
				bsp_DelayMS(1000);	
				HAL_GPIO_WritePin(GPIOC,J4_Pin,GPIO_PIN_RESET);//����
				bsp_DelayMS(500);
				HAL_GPIO_WritePin(GPIOB,J3_Pin,GPIO_PIN_SET);//����
				bsp_DelayMS(500);		
				HAL_GPIO_WritePin(GPIOA,J1_Pin,GPIO_PIN_RESET);//����
				HAL_GPIO_WritePin(GPIOA,J2_Pin,GPIO_PIN_SET);
				bsp_DelayMS(500);	
				//�����
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);//11 SERVO   
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);  
				bsp_DelayMS(5000);
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);   
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
		}
		
		
		
		
		
		//���봫����
	  range=VL6180X_Read_Range();
	//	printf("range is %d \r\n",range);
		if(range<100)
		{
			printf("o");//����С��100ʱ���˿Ϳ������봫����������'o'����λ������ѡ����Ҫ�����ϣ���
		}
		bsp_DelayMS(200);
	//����յ���λ��������ѡ���ź���ĸ����'p'����ɫ��������ʼ����
	if(re=='p')
	{	
		int i;
		//h������λ�����ͱ����
		if( re == 'h')
		{//��λ��Ҫ��ɫ����е�ۿ�ʼ��ת01�Ƕȣ���00��λ�ÿ�ʼת��ʶ��01��λ�ô��ĵ�һƿ����
				HAL_GPIO_WritePin(GPIOA,J1_Pin,GPIO_PIN_RESET);//��ת��01��λ��
				HAL_GPIO_WritePin(GPIOA,J2_Pin,GPIO_PIN_SET);
				bsp_DelayMS(500);
				//���ʶ����ɫ��		
				for(i=0;i<20;i++){//��ɫ��������������20��ȷ���ȶ�
					if(TCS34725_GetRawData(&rgb.r,&rgb.g,&rgb.b,&rgb.c))
					{
						if(rgb.r!=65535||rgb.g!=65535||rgb.b!=65535||rgb.c!=65535)
						{
							u16_r = (uint16_t)(1.2*rgb.r*255)/rgb.c;
							u16_g = (uint16_t)(1.6*rgb.g*255)/rgb.c;
							u16_b = (uint16_t)(1.4*rgb.b*255)/rgb.c;			
						}	
					}
				  bsp_DelayMS(100);	
				}
				if(u16_r <=200&&u16_r >=150&&u16_g >=100&&u16_b <=100&&u16_b <=200){		//ʶ����ɫ�����������
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);//01servo   
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);  
					printf("q\n");//���ظ���λ��'q';�����ͱ����
					bsp_DelayMS(5000);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);   
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
					bsp_DelayMS(500);
					zq01();//ץȡ���˿ʹ�
				}
		
				else{//10 position
						HAL_GPIO_WritePin(GPIOA,J1_Pin,GPIO_PIN_SET);//��ת10
						HAL_GPIO_WritePin(GPIOA,J2_Pin,GPIO_PIN_RESET);
						bsp_DelayMS(500);
										//���ʶ����ɫ��		//��ɫ��������������
						for(i=0;i<20;i++){
							if(TCS34725_GetRawData(&rgb.r,&rgb.g,&rgb.b,&rgb.c))
							{
								if(rgb.r!=65535||rgb.g!=65535||rgb.b!=65535||rgb.c!=65535)
								{
									u16_r = (uint16_t)(1.2*rgb.r*255)/rgb.c;
									u16_g = (uint16_t)(1.6*rgb.g*255)/rgb.c;
									u16_b = (uint16_t)(1.4*rgb.b*255)/rgb.c;			
								}	
							}
							bsp_DelayMS(100);
						}
						if(u16_r <=200&&u16_r >=150&&u16_g >=100&&u16_b <=100&&u16_b <=200){		//ʶ����ɫ�����������
							HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);   
							HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);  
							printf("q\n");//���ظ���λ��'q';�����ͱ����
							bsp_DelayMS(5000);
							HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);   
							HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
							bsp_DelayMS(500);
							zq10();//ץȡ���˿ʹ�
						}
						else{//11λ��
							HAL_GPIO_WritePin(GPIOA,J1_Pin,GPIO_PIN_SET);//��ת
							HAL_GPIO_WritePin(GPIOA,J2_Pin,GPIO_PIN_SET);
							bsp_DelayMS(500);
									//���ʶ����ɫ��		//��ɫ��������������
									for(i=0;i<20;i++){
										if(TCS34725_GetRawData(&rgb.r,&rgb.g,&rgb.b,&rgb.c))
										{
											if(rgb.r!=65535||rgb.g!=65535||rgb.b!=65535||rgb.c!=65535)
											{
												u16_r = (uint16_t)(1.2*rgb.r*255)/rgb.c;
												u16_g = (uint16_t)(1.6*rgb.g*255)/rgb.c;
												u16_b = (uint16_t)(1.4*rgb.b*255)/rgb.c;			
											}	
										}
										bsp_DelayMS(100);
									}
									if(u16_r <=200&&u16_r >=150&&u16_g >=100&&u16_b <=100&&u16_b <=200){		//ʶ����ɫ�����������
										HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);//11 SERVO   
										HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);  
										printf("q\n");//���ظ���λ��'q';�����ͱ����
										bsp_DelayMS(5000);
										HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);   
										HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
										bsp_DelayMS(500);
										zq11();//ץȡ���˿ʹ�
									}
						}
				}
		}
			
			
			
			
//e������λ�����ͺ�ţ
		else if ( re== 'e')  //10��ת90����ת��00(0��)
		{
			//�����ɫ������ʶ�𵽻�ɫ
				HAL_GPIO_WritePin(GPIOA,J1_Pin,GPIO_PIN_RESET);//��ת��01��λ��
				HAL_GPIO_WritePin(GPIOA,J2_Pin,GPIO_PIN_SET);
				bsp_DelayMS(500);		
				for(i=0;i<20;i++){//��ɫ��������������20��ȷ���ȶ�
					if(TCS34725_GetRawData(&rgb.r,&rgb.g,&rgb.b,&rgb.c))
					{
						if(rgb.r!=65535||rgb.g!=65535||rgb.b!=65535||rgb.c!=65535)
						{
							u16_r = (uint16_t)(1.2*rgb.r*255)/rgb.c;
							u16_g = (uint16_t)(1.6*rgb.g*255)/rgb.c;
							u16_b = (uint16_t)(1.4*rgb.b*255)/rgb.c;			
						}	
					}
					bsp_DelayMS(100);
				}
				if(u16_r <150&&u16_r >=110&&u16_g >=160&&u16_b <=100){		//ʶ�𵽻�ɫ�����������
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);   //01 SERVO
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);  
					printf("w\n");//���ظ���λ��'w';�����ͺ�ţ
					bsp_DelayMS(5000);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);   
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
					bsp_DelayMS(500);
					zq01();//ץȡ���˿ʹ�
				}
		
				else{//10 position
						HAL_GPIO_WritePin(GPIOA,J1_Pin,GPIO_PIN_SET);//��ת10
						HAL_GPIO_WritePin(GPIOA,J2_Pin,GPIO_PIN_RESET);
						bsp_DelayMS(500);
										//���ʶ����ɫ��		//��ɫ��������������
						for(i=0;i<20;i++){
							if(TCS34725_GetRawData(&rgb.r,&rgb.g,&rgb.b,&rgb.c))
							{
								if(rgb.r!=65535||rgb.g!=65535||rgb.b!=65535||rgb.c!=65535)
								{
									u16_r = (uint16_t)(1.2*rgb.r*255)/rgb.c;
									u16_g = (uint16_t)(1.6*rgb.g*255)/rgb.c;
									u16_b = (uint16_t)(1.4*rgb.b*255)/rgb.c;			
								}	
							}
							bsp_DelayMS(100);
						}
						if(u16_r <150&&u16_r >=110&&u16_g >=160&&u16_b <=100)		{		
							HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);   //10
							HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);  
							printf("w\n");
							bsp_DelayMS(5000);
							HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);   
							HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
							HAL_Delay(500);
							zq10();//ץȡ���˿ʹ�
						}
						else{//11λ��
							HAL_GPIO_WritePin(GPIOA,J1_Pin,GPIO_PIN_SET);//��ת11
							HAL_GPIO_WritePin(GPIOA,J2_Pin,GPIO_PIN_SET);
							bsp_DelayMS(500);
									for(i=0;i<20;i++){
										if(TCS34725_GetRawData(&rgb.r,&rgb.g,&rgb.b,&rgb.c))
										{
											if(rgb.r!=65535||rgb.g!=65535||rgb.b!=65535||rgb.c!=65535)
											{
												u16_r = (uint16_t)(1.2*rgb.r*255)/rgb.c;
												u16_g = (uint16_t)(1.6*rgb.g*255)/rgb.c;
												u16_b = (uint16_t)(1.4*rgb.b*255)/rgb.c;			
											}	
										}
										bsp_DelayMS(100);
									}
									if(u16_r <150&&u16_r >=110&&u16_g >=160&&u16_b <=100)		{		
										HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);   
										HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);  
										printf("w\n");
										bsp_DelayMS(5000);
										HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);   
										HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
										HAL_Delay(500);
										zq11();//ץȡ���˿ʹ�
									}
						}
				}
		}
		
//f presents that computer sends the letter 'f',����ţ��
		else if ( re == 'f')  //11��ת135����ת��00(0��)
		{
			//the color is white
		//�����ɫ������ʶ�𵽰�ɫ
				HAL_GPIO_WritePin(GPIOA,J1_Pin,GPIO_PIN_RESET);//��ת��01��λ��
				HAL_GPIO_WritePin(GPIOA,J2_Pin,GPIO_PIN_SET);
				bsp_DelayMS(500);		
				for(i=0;i<20;i++){//��ɫ��������������20��ȷ���ȶ�
					if(TCS34725_GetRawData(&rgb.r,&rgb.g,&rgb.b,&rgb.c))
					{
						if(rgb.r!=65535||rgb.g!=65535||rgb.b!=65535||rgb.c!=65535)
						{
							u16_r = (uint16_t)(1.2*rgb.r*255)/rgb.c;
							u16_g = (uint16_t)(1.6*rgb.g*255)/rgb.c;
							u16_b = (uint16_t)(1.4*rgb.b*255)/rgb.c;			
						}	
					}
					bsp_DelayMS(100);
				}
				if(u16_r <=100&&u16_g >=120&&u16_b >=110&&u16_b <=200)	{		//ʶ�𵽰�ɫ�����������
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);   //01
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);  
					printf("g\n");//���ظ���λ��'g';������ţ��
					HAL_Delay(5000);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);   
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
					HAL_Delay(500);
					zq01();//ץȡ���˿ʹ�
				}
		
				else{//10 position
						HAL_GPIO_WritePin(GPIOA,J1_Pin,GPIO_PIN_SET);//��ת10
						HAL_GPIO_WritePin(GPIOA,J2_Pin,GPIO_PIN_RESET);
						bsp_DelayMS(500);
						for(i=0;i<20;i++){
							if(TCS34725_GetRawData(&rgb.r,&rgb.g,&rgb.b,&rgb.c))
							{
								if(rgb.r!=65535||rgb.g!=65535||rgb.b!=65535||rgb.c!=65535)
								{
									u16_r = (uint16_t)(1.2*rgb.r*255)/rgb.c;
									u16_g = (uint16_t)(1.6*rgb.g*255)/rgb.c;
									u16_b = (uint16_t)(1.4*rgb.b*255)/rgb.c;			
								}	
							}
							bsp_DelayMS(100);
						}
						if(u16_r <=100&&u16_g >=120&&u16_b >=110&&u16_b <=200)	{		
							HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);   //10
							HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);  
							printf("g\n");
							HAL_Delay(5000);
							HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);   
							HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
							HAL_Delay(500);
							zq10();//ץȡ���˿ʹ�
						}
						else{//11λ��
							HAL_GPIO_WritePin(GPIOA,J1_Pin,GPIO_PIN_SET);//��ת11
							HAL_GPIO_WritePin(GPIOA,J2_Pin,GPIO_PIN_SET);
							bsp_DelayMS(500);
									for(i=0;i<20;i++){
										if(TCS34725_GetRawData(&rgb.r,&rgb.g,&rgb.b,&rgb.c))
										{
											if(rgb.r!=65535||rgb.g!=65535||rgb.b!=65535||rgb.c!=65535)
											{
												u16_r = (uint16_t)(1.2*rgb.r*255)/rgb.c;
												u16_g = (uint16_t)(1.6*rgb.g*255)/rgb.c;
												u16_b = (uint16_t)(1.4*rgb.b*255)/rgb.c;			
											}	
										}
										bsp_DelayMS(100);
									}
									if(u16_r <=100&&u16_g >=120&&u16_b >=110&&u16_b <=200)		{		
										HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);//11   
										HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);  
										printf("g\n");
										HAL_Delay(5000);
										HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);   
										HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
										HAL_Delay(500);
										zq11();//ץȡ���˿ʹ�
									}
						}
				}
		}
		else
		{
			//nothing received;
			printf("no\n");
			HAL_Delay(500);
			zq00();
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);   
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET); 
		}
	}//�����꣬����λ�������źţ�	

  }//while(1)

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, L0_Pin|L1_Pin|J1_Pin|J2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, J4_Pin|J5_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(J3_GPIO_Port, J3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, VL6180X_SCL_Pin|VL6180X_SDA_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : L0_Pin L1_Pin J1_Pin J2_Pin */
  GPIO_InitStruct.Pin = L0_Pin|L1_Pin|J1_Pin|J2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : J4_Pin J5_Pin */
  GPIO_InitStruct.Pin = J4_Pin|J5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : J3_Pin */
  GPIO_InitStruct.Pin = J3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(J3_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : VL6180X_SCL_Pin VL6180X_SDA_Pin */
  GPIO_InitStruct.Pin = VL6180X_SCL_Pin|VL6180X_SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/*
*********************************************************************************************************
*	�� �� ��: HAL_Delay
*	����˵��: �ض�������ӳٺ������滻HAL�еĺ�����
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/

void HAL_Delay(uint32_t Delay)
{
	bsp_DelayMS(Delay);
}

int fputc(int ch,FILE *f)
{
	//printf����ض���
	uint8_t temp=ch;
	HAL_UART_Transmit(&huart1,&temp,1,2);
	
	HAL_UART_Transmit(&huart2,&temp,1,2);
	return temp;
}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

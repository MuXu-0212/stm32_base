#include "sys.h"

int main()
{
	
/********************************LED��ʵ��****************************/
//	LED_Init();
//	KEY_Init();
//	
//	while(1)
//	{
//		GPIOF->BSRRH = GPIO_Pin_9 | GPIO_Pin_10;
//		GPIOE->BSRRH = GPIO_Pin_13 | GPIO_Pin_14;	
//	}

/*=================================================================================*/

/********************************LED & KEY ��ʵ��****************************/
//	u32 flag = 1;
//	LED_Init();
//	KEY_Init();
//	
//	GPIOF->BSRRH = GPIO_Pin_9 | GPIO_Pin_10;
//	GPIOE->BSRRL = GPIO_Pin_13 | GPIO_Pin_14;
//	
//	while(1)
//	{
//		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == Bit_RESET && flag == 1)
//		{
//			delay_led();
//			if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == Bit_RESET && flag == 1)
//			{
//				GPIOF->ODR ^= GPIO_Pin_9 | GPIO_Pin_10;
//				GPIOE->ODR ^= GPIO_Pin_13 | GPIO_Pin_14;
//				flag = 0;
//				
//			}
//		}
//		else if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2) == Bit_RESET && flag == 0)
//		{
//			delay_led();
//			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2) == Bit_RESET && flag == 0)
//			{
//				GPIOF->ODR ^= GPIO_Pin_9 | GPIO_Pin_10;
//				GPIOE->ODR ^= GPIO_Pin_13 | GPIO_Pin_14;
//				flag = 1;
//			}
//		}
//	}
/*=================================================================================*/

/*****************************EXTI�ж�******************************/
//	LED_Init();
//	EXTILine0_Init();
//	
//	while(1)
//	{
//		
//	}
/*=================================================================================*/

/*****************************ϵͳ��ʱ��1******************************/	

//	LED_Init();
//	
//	PFout(9)=0;
//	PFout(10)=0;
//	PEout(13)=0;
//	PEout(14)=0;
//	
//	SYS_TIMER();


//	while(1)
//	{
//		
//	}

/*=================================================================================*/
	
	
/*****************************ϵͳ��ʱ��2*****************************/	
	
//	LED_Init();
//	
//	PFout(9)=1;
//	PFout(10)=1;
//	PEout(13)=1;
//	PEout(14)=1;
//	
//	while(1)
//	{
//		PFout(9)^=1;
//		delay_ms(500);
//		PFout(10)^=1;
//		delay_ms(500);
//		PEout(13)^=1;
//		delay_ms(500);
//		PEout(14)^=1;
//		delay_ms(500);
//	}
	
	
/*=================================================================================*/
	
	
/*****************************Ӳ����ʱ��*****************************/	
	
//	LED_Init();
//	
//	PFout(9)=1;
//	TIM3_INIT();
//	
//	while(1)
//	{

//	}
	
	
/*=================================================================================*/

/*******************************pwm****************************/	
//	u32 pwm_cmp;
//	LED_Init();
//	PFout(9)=0;
//	PFout(10)=1;
//	PEout(13)=1;
//	PEout(14)=1;
//	TIM14_Init();
//	while(1)
//	{
//		//����
//		for(pwm_cmp=0; pwm_cmp<=100; pwm_cmp++)
//		{
//			TIM_SetCompare1(TIM14, pwm_cmp);
//			
//			delay_ms(20);
//		}
//		delay_ms(1000);
//		//����
//		for(pwm_cmp=100; pwm_cmp>0; pwm_cmp--)
//		{
//			TIM_SetCompare1(TIM14, pwm_cmp);
//			
//			delay_ms(20);
//		}
//	}
//	
	
/*=================================================================================*/

/*******************************pwm2****************************/	
//	u32 pwm_cmp;
//	LED_Init();
//	PFout(9)=0;
//	PFout(10)=1;
//	PEout(13)=1;
//	PEout(14)=1;
//	TIM14_Init();
//	while(1)
//	{
//		//����
//		for(pwm_cmp=0; pwm_cmp<=100; pwm_cmp++)
//		{
//			TIM_SetCompare1(TIM14, pwm_cmp);
//			
//			delay_ms(20);
//		}
//		delay_ms(1000);
//		//����
//		for(pwm_cmp=100; pwm_cmp>0; pwm_cmp--)
//		{
//			TIM_SetCompare1(TIM14, pwm_cmp);
//			
//			delay_ms(20);
//		}
//	}
	
	
/*=================================================================================*/


/*******************************������****************************/	
//	//����1������
//	LED_Init();
//	PFout(9)=1;
//	USART1_Init(115200);
//	
//	USART_SendData(USART1, 'G');
//	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
//	USART_SendData(USART1, 'E');
//	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
//	
//	printf("123\r\n");
//	while(1)
//	{
//		
//	}
	
	
/*=================================================================================*/

/*******************************��������������****************************/	


//	LED_Init();
//	PFout(9)=1;
//	//����3������
////	USART3_Init(9600);
//	USART1_Init(115200);

//	PFout(10)=1;
//	
//	
//	//����ģ�������
////	Ble_Config_Set();
//	
//	while(1)
//	{
//		
//	}
	
	
/*=================================================================================*/

/*******************************��ʪ��****************************/	

//	u8 dht11_data[5];
//	USART1_Init(115200);
//	DHT11_Init();
//	
//	
//	while(1)
//	{
//		DHT11_Read(dht11_data);

//		printf("ʪ��:%d.%d  �¶�:%d.%d ��\r\n", dht11_data[0],dht11_data[1],dht11_data[2],dht11_data[3]);
//		delay_ms(500);
//	}


	
	
/*=================================================================================*/



/*******************************RTC****************************/	
//	USART1_Init(115200);
//	rtc_init();

//	//���ݼĴ���
//	if (RTC_ReadBackupRegister(RTC_BKP_DR0) != 0x1688)
//	{  
//		//���ñ��ݼĴ���0
//		RTC_WriteBackupRegister(RTC_BKP_DR0, 0x1688);
//	}
//	else
//	{
//		rtc_reinit();
//	}

//	while(1)
//	{
//		RTC_Print();
//		delay_ms(1000);
//	}
	
	
/*=================================================================================*/


/*******************************IWDG****************************/	
//	USART1_Init(115200);
//	IWDG_Init();
//	
//	printf("this is iwdg test\r\n");
//	while(1)
//	{
//		//....��ʪ��
//		//....��ѹ�ɼ�
//		//....�������ݴ���
//		
//		//�ӳٳ������ƣ���һֱ������λ
//		delay_ms(1500);
//		//ˢ�¼���ֵ == ι������ֹ����ֵ����0�ʹ�����λ
//		IWDG_ReloadCounter();
//	}
	
	
/*=================================================================================*/

/*******************************IWDG//������****************************/	
//	u8 buf[5];
//	u32 rt;
//	USART1_Init(115200);
//	DHT11_Init();
//	IWDG_Init();
//	
//	printf("this is iwdg test\r\n");
//	while(1)
//	{
//		rt = DHT11_Read(buf);
//		if (rt == 0)
//		{
//			printf("�¶�:%d.%d, ʪ��:%d.%d", buf[2], buf[3], buf[0], buf[1]);
//			if(buf[2] >= 29)
//			{
//				iwdg_flag=0;
//			}
//		}
//		else
//		{
//			//printf("dhtll error code %d\r\n", rt);
//		}
//		delay_ms(1000);

//	}
//	
	
/*=================================================================================*/


/*******************************WWDG****************************/	
//	USART1_Init(115200);
//	WWDG_Init();
//	printf("This is wwdg test\r\n");
//	while(1)
//	{
//		delay_ms(40);
//		//ι��
//		WWDG_SetCounter(127);
//		
//	}
	
/*=================================================================================*/

/*******************************IWDG//������****************************/	
//	u8 buf[5];
//	u32 rt;
//	USART1_Init(115200);
//	DHT11_Init();
//	IWDG_Init();
//	
//	printf("this is iwdg test\r\n");
//	while(1)
//	{
//		rt = DHT11_Read(buf);
//		if (rt == 0)
//		{
//			printf("�¶�:%d.%d, ʪ��:%d.%d", buf[2], buf[3], buf[0], buf[1]);
//			if(buf[2] >= 29)
//			{
//				iwdg_flag=0;
//			}
//		}
//		else
//		{
//			//printf("dhtll error code %d\r\n", rt);
//		}
//		delay_ms(1000);

//	}
	
/*=================================================================================*/


/*******************************ADC****************************/	
//	uint16_t adc_val, adc_vol;
//	
//	USART1_Init(115200);
//	adc_init();
//	
//	//����ADC
//	ADC_SoftwareStartConv(ADC1);
//	
//	while(1)
//	{
//		//�ȴ�ADC1ת�����
//		while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
//		ADC_ClearFlag( ADC1, ADC_FLAG_EOC);
//		
//		//�õ����ֵ
//		adc_val = ADC_GetConversionValue(ADC1);
//		
//		//�����ֵת��Ϊ��ѹֵ
//		adc_vol = adc_val * 3300/4905;
//		printf("adc_val:%d\r\n",adc_val);
//		printf("adc_vol:%d\r\n",adc_vol);
//	}
	
	
/*=================================================================================*/

/*******************************ADC****************************/	
//	uint16_t adc_val, adc_vol;
//	
//	USART1_Init(115200);
//	adc_init();
//	
//	//����ADC
//	ADC_SoftwareStartConv(ADC1);
//	
//	while(1)
//	{
//		//�ȴ�ADC1ת�����
//		while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
//		ADC_ClearFlag( ADC1, ADC_FLAG_EOC);
//		
//		//�õ����ֵ
//		adc_val = ADC_GetConversionValue(ADC1);
//		
//		//�����ֵת��Ϊ��ѹֵ
//		adc_vol = adc_val * 3300/4905;
//		printf("adc_val:%d\r\n",adc_val);
//		printf("adc_vol:%d\r\n",adc_vol);
//	}
	
	
/*=================================================================================*/
/*******************************spi  W25qxx****************************/	
	
	
	USART1_Init(115200);
	w25qxx_Init();
	
	
}





#include "sys.h"

int main()
{
	
/********************************LED的实现****************************/
//	LED_Init();
//	KEY_Init();
//	
//	while(1)
//	{
//		GPIOF->BSRRH = GPIO_Pin_9 | GPIO_Pin_10;
//		GPIOE->BSRRH = GPIO_Pin_13 | GPIO_Pin_14;	
//	}

/*=================================================================================*/

/********************************LED & KEY 的实现****************************/
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

/*****************************EXTI中断******************************/
//	LED_Init();
//	EXTILine0_Init();
//	
//	while(1)
//	{
//		
//	}
/*=================================================================================*/

/*****************************系统定时器1******************************/	

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
	
	
/*****************************系统定时器2*****************************/	
	
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
	
	
/*****************************硬件定时器*****************************/	
	
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
//		//渐灭
//		for(pwm_cmp=0; pwm_cmp<=100; pwm_cmp++)
//		{
//			TIM_SetCompare1(TIM14, pwm_cmp);
//			
//			delay_ms(20);
//		}
//		delay_ms(1000);
//		//渐亮
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
//		//渐灭
//		for(pwm_cmp=0; pwm_cmp<=100; pwm_cmp++)
//		{
//			TIM_SetCompare1(TIM14, pwm_cmp);
//			
//			delay_ms(20);
//		}
//		delay_ms(1000);
//		//渐亮
//		for(pwm_cmp=100; pwm_cmp>0; pwm_cmp--)
//		{
//			TIM_SetCompare1(TIM14, pwm_cmp);
//			
//			delay_ms(20);
//		}
//	}
	
	
/*=================================================================================*/


/*******************************波特率****************************/	
//	//串口1波特率
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

/*******************************蓝牙，包括改名****************************/	


//	LED_Init();
//	PFout(9)=1;
//	//串口3波特率
////	USART3_Init(9600);
//	USART1_Init(115200);

//	PFout(10)=1;
//	
//	
//	//蓝牙模块的配置
////	Ble_Config_Set();
//	
//	while(1)
//	{
//		
//	}
	
	
/*=================================================================================*/

/*******************************温湿度****************************/	

//	u8 dht11_data[5];
//	USART1_Init(115200);
//	DHT11_Init();
//	
//	
//	while(1)
//	{
//		DHT11_Read(dht11_data);

//		printf("湿度:%d.%d  温度:%d.%d ℃\r\n", dht11_data[0],dht11_data[1],dht11_data[2],dht11_data[3]);
//		delay_ms(500);
//	}


	
	
/*=================================================================================*/



/*******************************RTC****************************/	
//	USART1_Init(115200);
//	rtc_init();

//	//备份寄存器
//	if (RTC_ReadBackupRegister(RTC_BKP_DR0) != 0x1688)
//	{  
//		//设置备份寄存器0
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
//		//....温湿度
//		//....电压采集
//		//....蓝牙数据传输
//		
//		//延迟超过限制，会一直触发复位
//		delay_ms(1500);
//		//刷新计数值 == 喂狗，防止计数值减到0就触发复位
//		IWDG_ReloadCounter();
//	}
	
	
/*=================================================================================*/

/*******************************IWDG//有问题****************************/	
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
//			printf("温度:%d.%d, 湿度:%d.%d", buf[2], buf[3], buf[0], buf[1]);
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
//		//喂狗
//		WWDG_SetCounter(127);
//		
//	}
	
/*=================================================================================*/

/*******************************IWDG//有问题****************************/	
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
//			printf("温度:%d.%d, 湿度:%d.%d", buf[2], buf[3], buf[0], buf[1]);
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
//	//启动ADC
//	ADC_SoftwareStartConv(ADC1);
//	
//	while(1)
//	{
//		//等待ADC1转换完毕
//		while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
//		ADC_ClearFlag( ADC1, ADC_FLAG_EOC);
//		
//		//得到结果值
//		adc_val = ADC_GetConversionValue(ADC1);
//		
//		//将结果值转换为电压值
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
//	//启动ADC
//	ADC_SoftwareStartConv(ADC1);
//	
//	while(1)
//	{
//		//等待ADC1转换完毕
//		while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
//		ADC_ClearFlag( ADC1, ADC_FLAG_EOC);
//		
//		//得到结果值
//		adc_val = ADC_GetConversionValue(ADC1);
//		
//		//将结果值转换为电压值
//		adc_vol = adc_val * 3300/4905;
//		printf("adc_val:%d\r\n",adc_val);
//		printf("adc_vol:%d\r\n",adc_vol);
//	}
	
	
/*=================================================================================*/
/*******************************spi  W25qxx****************************/	
	
	
	USART1_Init(115200);
	w25qxx_Init();
	
	
}





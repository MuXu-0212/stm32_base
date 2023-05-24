#include "sys.h"

static EXTI_InitTypeDef   EXTI_InitStructure;
static GPIO_InitTypeDef   GPIO_InitStructure;
static NVIC_InitTypeDef   NVIC_InitStructure;


//外部中断初始化
void EXTILine0_Init(void)
{
	/* Enable GPIOA clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	/* Enable SYSCFG clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* Configure PA0 pin as input floating */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Connect EXTI Line0 to PA0 pin */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

	/* Configure EXTI Line0 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;				//外部中断0
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		//中断
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  //下降沿触发，用于识别按键的按下
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//使能
	EXTI_Init(&EXTI_InitStructure);

	/* Enable and set EXTI Line0 Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//外部中断0的请求通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;       //响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //使能该通道
	NVIC_Init(&NVIC_InitStructure);
	
	//RESET为0
	GPIO_SetBits( GPIOF, GPIO_Pin_9 | GPIO_Pin_10);
	GPIO_ResetBits( GPIOE, GPIO_Pin_13 | GPIO_Pin_14);
	
}
 



//中断服务interrupt serve source
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) == SET)
	{

		/* function */
		//PFout(9) = 0;
		GPIOF->ODR ^= GPIO_Pin_9;
		GPIOF->ODR ^= GPIO_Pin_10;
		GPIOE->ODR ^= GPIO_Pin_13;
		GPIOE->ODR ^= GPIO_Pin_14;

		 /* Clear the EXTI line 0 pending bit */
		EXTI_ClearITPendingBit(EXTI_Line0);

	}

}


void SYS_TIMER(void)
{
	//系统定时器的时钟源168MHz
	//只要系统定时器进行168 00 0000个计数，就代表1秒钟时间的到达
	//只要系统定时器进行168 00 0000/10个计数，就代表1/10秒钟时间的到达
	//只要系统定时器进行168 00 0000/100个计数，就代表1/100秒钟的到达
#if 0
	//配置系统定时器触发1000Hz的中断
	//周期时间T=1/f=1/10Hz=100ms
	SysTick_Config(SystemCoreClock / 10);
	//灯不会亮或时间不准确的原因，16800 0000/10=1680 0000,超过了计数器2^24=1677 7216的范围
#endif

#if 0
	//配置系统定时器触发1000Hz的中断
	//周期时间T=1/f=1/10Hz=1ms
	SysTick_Config(SystemCoreClock / 1000);
#endif

#if 0
	//配置系统定时器触发1000Hz的中断
	//周期时间T=1/f=1=1s
	SysTick_Config(SystemCoreClock);
#endif
}

//系统定时器
//void SysTick_Handler(void)
//{
//	static uint32_t i=0; 
//	static uint32_t j=0; 
//	static uint32_t k=0; 
//	static uint32_t h=0;
//	
//	i++;
//	j++;
//	k++;
//	h++;
//	if(i>=100)
//	{
//		i=0;
//		//灯状态的翻转
//		PFout(9)^=1;	//1^0=1		1^1=0	0^1=1	1^1=0
//	}
//	if(j>=330)
//	{
//		j=0;
//		PFout(10)^=1;
//	}
//	if(k>=1500)
//	{
//		k=0;
//		PEout(13)^=1;
//	}
//	if(h>=2200)
//	{
//		h=0;
//		PEout(14)^=1;
//	}
//}

/*
//毫秒定时器定时
void delay_ms(uint32_t n)
{
#if 0
	while(n--)
	{
		SysTick->CTRL = 0; // Disable SysTick
		SysTick->LOAD = (168000)-1; // Count from 255 to 0 (256 cycles)
		SysTick->VAL = 0; // Clear current value as well as count flag
		SysTick->CTRL = 5; // Enable SysTick timer with processor clock
		while ((SysTick->CTRL & 0x00010000)==0);// Wait until count flag is set
	}
	SysTick->CTRL = 0; // Disable SysTick
#endif
	
#if 0
	//当系统使用时钟的八分频，这个时候系统定时器的时钟源=168MHz/8=21MHz
	//只要进行2100 0000个计数，就代表1秒钟时间的到达
	//只要2100 0000个计数，就代表1/1000秒钟时间的到达
	while(n--)
	{
		SysTick->CTRL = 0; // Disable SysTick
		SysTick->LOAD = (21000)-1; // Count from 255 to 0 (256 cycles) 配置计数值(21000)-1 ~ 0
		SysTick->VAL = 0; // Clear current value as well as count flag
		SysTick->CTRL = 1; // Enable SysTick timer with processor clock
		while ((SysTick->CTRL & 0x00010000)==0);// Wait until count flag is set
	}
	SysTick->CTRL = 0; // Disable SysTick	
#endif
}
*/

//毫秒定时器定时
#if 1
uint32_t delay_ms(uint32_t n)
{
	while(n--)
	{
		SysTick->CTRL = 0; 				// Disable SysTick，关闭系统定时器
		SysTick->LOAD = (168000)-1; 	// 配置计数值(168000)-1 ~ 0
		SysTick->VAL  = 0; 		// Clear current value as well as count flag
		SysTick->CTRL = 5; 		// Enable SysTick timer with processor clock
		while ((SysTick->CTRL & 0x10000)==0);// Wait until count flag is set
	}
	
	SysTick->CTRL = 0; 		// Disable SysTick	
	
	

//	uint32_t temp;
//	SysTick->LOAD = n * 22500;	//计数器需要递减
//	SysTick->VAL = 0;	//计数器清零
//	SysTick->CTRL |=1;	//开启计数器
//    
//	//等待计数器中的数值被减到0
//	do{
//		temp = SysTick->CTRL;
//	}while( !(temp & (1<<16)) && (temp&0x01) );
//	//这里写！，是因为寄存器为0时要继续循环，
//	//当触发中断时，ctrl寄存器的第0bit会强制置为0
//	
//	SysTick->CTRL &= ~1;	//关闭计数器
	return 0;
}
#endif

//微秒定时器定时
uint32_t delay_us(uint32_t n)
{

	SysTick->CTRL = 0; // Disable SysTick
	SysTick->LOAD = (168*n)-1; // Count from 255 to 0 (256 cycles)
	SysTick->VAL = 0; // Clear current value as well as count flag
	SysTick->CTRL = 5; //0101 Enable SysTick timer with processor clock
	while ((SysTick->CTRL & 0x00010000)==0);// Wait until count flag is set
	SysTick->CTRL = 0; // Disable SysTick
	
	
//	uint32_t temp;

//	SysTick->CTRL = 0;                     
//	SysTick->LOAD = (n*21)-1;         
//	SysTick->VAL = 0;                     
//	SysTick->CTRL = 1;                     

//	while(1)
//	{
//		temp=SysTick->CTRL;
//		//检测count flag
//		if(temp & 0x00010000)
//		{
//				break;
//		}
//		//检测系统定时器是否意外关闭    
//		if((temp & 0x1)==0)
//		{
//			return -1;    
//		}
//	}

//	SysTick->CTRL = 0; 
	return 0;
	
	
}





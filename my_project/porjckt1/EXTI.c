#include "myhead.h"

static GPIO_InitTypeDef Key_init;
static EXTI_InitTypeDef EXTI_InitStruct;
static NVIC_InitTypeDef NVIC_InitStruct;
	
void EXTI0_Init(void)
{
	//使能时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	//使能中断线时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	

	Key_init.GPIO_Pin  	= GPIO_Pin_0;
	Key_init.GPIO_Mode 	= GPIO_Mode_IN;
	Key_init.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	Key_init.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &Key_init);
	
	//让我们初始化好的引脚 与 中断线进行连接  让PA0号引脚进行连接中断
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource0);
	
	
	//中断配置
	EXTI_InitStruct.EXTI_Line 		= EXTI_Line0;            //选择那一条中断线
	EXTI_InitStruct.EXTI_Mode 		= EXTI_Mode_Interrupt;   //中断
	EXTI_InitStruct.EXTI_Trigger	= EXTI_Trigger_Falling;  //下降沿触发
	EXTI_InitStruct.EXTI_LineCmd	= ENABLE;  				 //使能这条中断线
	EXTI_Init(&EXTI_InitStruct);
	
	//配置中断通道和中断优先级
	NVIC_InitStruct.NVIC_IRQChannel						= EXTI0_IRQn;   //选择中断通道
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority	= 0x02;  		//抢占优先级 0~3
	NVIC_InitStruct.NVIC_IRQChannelSubPriority			= 0x02 ;  		//响应优先级 0~3
	NVIC_InitStruct.NVIC_IRQChannelCmd  				= ENABLE;		//使能中断通道
	
	NVIC_Init(&NVIC_InitStruct);
	
	//配置中断优先级分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
}

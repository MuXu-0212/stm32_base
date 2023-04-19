#include "sys.h"


static NVIC_InitTypeDef NVIC_InitStruct;

//窗口看门狗初始化
void WWDG_Init(void)
{
	//使能窗口看门狗的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
	
	//设置预分频 我们的WWDG工作频率为 42Mhz
	//WWDG_Prescaler_8: WWDG counter clock = (PCLK1/4096)/8 = 1281HZ
	WWDG_SetPrescaler(WWDG_Prescaler_8);
	
	//设置窗口看门狗的上限值 取值范围可以是 64 ~ 127  上限49 底线36.6 
	// 64 ~ 80之间才是一个有效喂狗  数一个数为 780us * （127 - 80）
	WWDG_SetWindowValue(80);
	
	//设置计数值的上限,并使能看门进行工作
	WWDG_Enable(127);
}

void WWDG_Exti_Init(void)
{
	//使能窗口看门狗的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);

	//设置窗口看门狗分频,分频值越大,计数时间越长
	//WWDG counter clock = (PCLK1/4096)/8
	//工作频率: 42Mhz / 4096 / 8 = 1281Hz  
	//以现在的一个工作频率 也就是意味着1秒数1281个数
	//那计一个数则为 1000ms / 1281 = 0.7806 1us 计 780.6 个数
	WWDG_SetPrescaler(WWDG_Prescaler_8);
	
	//设置时间窗口的上限值
	WWDG_SetWindowValue(80);
	
	//使能提前唤醒中断
    WWDG_EnableIT();
	//窗口看门狗中断优先级配置
    NVIC_InitStruct.NVIC_IRQChannel		  			  = WWDG_IRQn;	//配置中断通道
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x01;       //配置响应优先级
    NVIC_InitStruct.NVIC_IRQChannelSubPriority	  	  = 0x02;	//配置抢占优先级
    NVIC_InitStruct.NVIC_IRQChannelCmd		  		  = ENABLE;     //使能工作
    NVIC_Init(&NVIC_InitStruct);
	
	//设置计数值，并使能窗口看门狗工作
	WWDG_Enable(127);
 }


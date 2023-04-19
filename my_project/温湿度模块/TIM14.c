#include "sys.h"

static TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
static NVIC_InitTypeDef NVIC_InitStruct;


//挂载在APB1总线上  工作频率为84MHZ    84000 000 / 8400 = 10000
void TIM14_Init(void)
{
	//1.使能时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
	
	//2.配置定时器,初始化函数
	TIM_TimeBaseInitStruct.TIM_Period  	 	= 10000;	//计数值, 计数的值决定了定时时间 0 ~ 65535
	TIM_TimeBaseInitStruct.TIM_Prescaler 	= 8400-1;   //预分频，0 ~ 65535
	TIM_TimeBaseInitStruct.TIM_CounterMode	= TIM_CounterMode_Up; //向上计数
	TIM_TimeBaseInit(TIM14, &TIM_TimeBaseInitStruct);
	
	//3.让定时怎么工作
	TIM_ITConfig(TIM14, TIM_IT_Update, ENABLE);
	
	//4.配置定时器的通道
	NVIC_InitStruct.NVIC_IRQChannel					    = TIM8_TRG_COM_TIM14_IRQn; //配置中断通道
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority	= 0x02;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority			= 0x02;
	NVIC_InitStruct.NVIC_IRQChannelCmd					= ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
	//5.使能定时器开始工作
	TIM_Cmd(TIM14, ENABLE);	
}

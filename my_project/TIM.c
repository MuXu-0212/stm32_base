#include "sys.h"

static   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
static   TIM_OCInitTypeDef  TIM_OCInitStructure;
static   NVIC_InitTypeDef  NVIC_InitStructure;



//硬件定时器---定时器3的初始化
void TIM3_INIT(void)
{
	//使能定时器3硬件时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	//配置定时器3分频值、计数值等
	TIM_TimeBaseStructure.TIM_Period = (10000/2)-1;     			//计数值，0~9999，决定定时时间
	TIM_TimeBaseStructure.TIM_Prescaler = 8400-1;		//8400-1+1=8400，进行8400的预分频值
	//TIM_TimeBaseStructure.TIM_ClockDivision = 0;    					//在F407不支持	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数的方法
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	
	//配置定时器3中断的触发方式：时间更新
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	
	//配置定时器3的中断优先级
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	
	//使能定时器3工作
	TIM_Cmd(TIM3, ENABLE);


}

void TIM3_IRQHandler(void)
{
	//判断标志位
	if(TIM_GetITStatus(TIM3, TIM_IT_Update)==SET)
	{
		PFout(9) ^= 1;
		
		//清空标志位
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
	
}


//独立看门狗
//void TIM3_IRQHandler(void)
//{
//	//判断标志位
//	if (SET==TIM_GetITStatus(TIM3, TIM_IT_Update))
//	{
//		if(iwdg_flag)
//		{
//			//没500ms喂一次狗，CPU不复位
//			IWDG_ReloadCounter();//刷新计数值 == 喂狗，防止计数值减到0触发复位
//		}
//		//清空标志位
//		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
//	}
//}














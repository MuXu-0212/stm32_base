#include "sys.h"

static TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
static TIM_OCInitTypeDef  TIM_OCInitStructure;
//static NVIC_InitTypeDef  NVIC_InitStructure;
static GPIO_InitTypeDef  GPIO_InitStructure;


//定时器14的初始化
void TIM14_Init(void)
{
	/* GPIOG 外部时钟使能 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	/* Enable TIM14 clocks */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14 , ENABLE);
	
	/* 配置PG9的推挽输出模式*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	//第9跟引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	//复用功能模式，该引脚交给其他硬件自动管理
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	//推挽输出，增加输出电流能力
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//高速响应
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	//没有使能上下拉电阻
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	
    //将引脚与定时器14进行链接
    GPIO_PinAFConfig(GPIOF,GPIO_PinSource9,GPIO_AF_TIM14);
	
	//配置定时器14分频值、计数值等
	TIM_TimeBaseStructure.TIM_Period = (10000/100)-1;     //计数值，0~99，决定输出频率为100Hz
	//TIM_TimeBaseStructure.TIM_Period = (10000/20)-1;     //计数值，0~499，决定输出频率为20Hz
	TIM_TimeBaseStructure.TIM_Prescaler = 8400-1;		//8400-1+1=8400，进行8400的预分频值
	//TIM_TimeBaseStructure.TIM_ClockDivision = 0;    					//在F407不支持	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数的方法
	TIM_TimeBaseInit(TIM14, &TIM_TimeBaseStructure);
	
	
//	//配置定时器3中断的触发方式：时间更新
//	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	
//	//配置定时器3的中断优先级
//	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);


	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;				
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//打开/关闭脉冲输出
	TIM_OCInitStructure.TIM_Pulse = 50;								//比较值决定占空比, 比较值=占空比*(最大计数值(99)+1)
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       //有效状态为高电平，则无效状态为低电平

	TIM_OC1Init(TIM14, &TIM_OCInitStructure);

	
	//使能定时器14工作
	TIM_Cmd(TIM14, ENABLE);
}


void TIM1_Init(void)
{
	//使能定时器1硬件时钟
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);
	/* GPIOG 外部时钟使能 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
//	/* Enable TIM1 clocks */
//	RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);
	
	/* 配置PG9的推挽输出模式*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	//第9跟引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	//复用功能模式，该引脚交给其他硬件自动管理
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	//推挽输出，增加输出电流能力
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//高速响应
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	//没有使能上下拉电阻
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	
    //将引脚与定时器1进行链接
    GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_TIM1);
	
	//配置定时器1分频值、计数值等
	//定时器1硬件时钟频率=(84MHz * 2)/TIM_Prescaler(16800) = 10000Hz
	TIM_TimeBaseStructure.TIM_Period = (10000/100)-1;     //计数值，0~99，决定输出频率为100Hz
	//TIM_TimeBaseStructure.TIM_Period = (10000/20)-1;     //计数值，0~499，决定输出频率为20Hz
	TIM_TimeBaseStructure.TIM_Prescaler = 16800-1;		//8400-1+1=8400，进行8400的预分频值
	//TIM_TimeBaseStructure.TIM_ClockDivision = 0;    					//在F407不支持	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数的方法
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;				
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//打开/关闭脉冲输出
	TIM_OCInitStructure.TIM_Pulse = 100;								//比较值决定占空比, 比较值=占空比*(最大计数值(99)+1)
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       //有效状态为高电平，则无效状态为低电平

	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	
	//使能定时器1工作
	TIM_Cmd(TIM1, ENABLE);
	
	
	//控制PWM的主输出
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
}









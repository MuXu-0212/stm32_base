#include "sys.h"

static GPIO_InitTypeDef GPIO_InitStruct;
static TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
static TIM_OCInitTypeDef TIM_OCInitStruct;

void TIM14_CH1_PWM(void)
{
	//1.使能时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	//2.配置引脚
	GPIO_InitStruct.GPIO_Pin  	= GPIO_Pin_9 ;   	//初始化PF9号引脚
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AF;		//配置引脚为复用模式
	GPIO_InitStruct.GPIO_Speed	= GPIO_High_Speed;  //配置为高速响应 100Mhz
	GPIO_InitStruct.GPIO_OType 	= GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_NOPULL; //浮空模式 既不上拉也不下拉
	GPIO_Init(GPIOF,&GPIO_InitStruct);
	
	//3.引脚与定时器相连接
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource9, GPIO_AF_TIM14);
	
	//4.配置定时器输出频率
	TIM_TimeBaseInitStruct.TIM_Period	 	= 100-1; //10MS 计数值
	TIM_TimeBaseInitStruct.TIM_Prescaler 	= 8400-1; //84000 000/ 8400 = 10000
	TIM_TimeBaseInitStruct.TIM_CounterMode 	= TIM_CounterMode_Up; //向上计数
	TIM_TimeBaseInit(TIM14, &TIM_TimeBaseInitStruct);
	
	//5.定时器的输出通道以及模式
	TIM_OCInitStruct.TIM_OCMode       =  TIM_OCMode_PWM1;       	//你要使用什么模式工作
	TIM_OCInitStruct.TIM_OutputState  =  TIM_OutputState_Enable;    //开启与关闭脉冲输出
	TIM_OCInitStruct.TIM_OCPolarity   =  TIM_OCPolarity_High;       //有效电平为高电平
	TIM_OCInitStruct.TIM_Pulse        =	 50;						//比较值 一定要在计数值的范围内
	TIM_OC1Init(TIM14, &TIM_OCInitStruct);
	
	//6.使能定时器
	TIM_Cmd(TIM14, ENABLE);
}

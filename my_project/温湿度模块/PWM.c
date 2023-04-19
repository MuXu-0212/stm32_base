#include "sys.h"

static GPIO_InitTypeDef GPIO_InitStruct;
static TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
static TIM_OCInitTypeDef TIM_OCInitStruct;

void TIM14_CH1_PWM(void)
{
	//1.ʹ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	//2.��������
	GPIO_InitStruct.GPIO_Pin  	= GPIO_Pin_9 ;   	//��ʼ��PF9������
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AF;		//��������Ϊ����ģʽ
	GPIO_InitStruct.GPIO_Speed	= GPIO_High_Speed;  //����Ϊ������Ӧ 100Mhz
	GPIO_InitStruct.GPIO_OType 	= GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_NOPULL; //����ģʽ �Ȳ�����Ҳ������
	GPIO_Init(GPIOF,&GPIO_InitStruct);
	
	//3.�����붨ʱ��������
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource9, GPIO_AF_TIM14);
	
	//4.���ö�ʱ�����Ƶ��
	TIM_TimeBaseInitStruct.TIM_Period	 	= 100-1; //10MS ����ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler 	= 8400-1; //84000 000/ 8400 = 10000
	TIM_TimeBaseInitStruct.TIM_CounterMode 	= TIM_CounterMode_Up; //���ϼ���
	TIM_TimeBaseInit(TIM14, &TIM_TimeBaseInitStruct);
	
	//5.��ʱ�������ͨ���Լ�ģʽ
	TIM_OCInitStruct.TIM_OCMode       =  TIM_OCMode_PWM1;       	//��Ҫʹ��ʲôģʽ����
	TIM_OCInitStruct.TIM_OutputState  =  TIM_OutputState_Enable;    //������ر��������
	TIM_OCInitStruct.TIM_OCPolarity   =  TIM_OCPolarity_High;       //��Ч��ƽΪ�ߵ�ƽ
	TIM_OCInitStruct.TIM_Pulse        =	 50;						//�Ƚ�ֵ һ��Ҫ�ڼ���ֵ�ķ�Χ��
	TIM_OC1Init(TIM14, &TIM_OCInitStruct);
	
	//6.ʹ�ܶ�ʱ��
	TIM_Cmd(TIM14, ENABLE);
}

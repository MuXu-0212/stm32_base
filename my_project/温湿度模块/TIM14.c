#include "sys.h"

static TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
static NVIC_InitTypeDef NVIC_InitStruct;


//������APB1������  ����Ƶ��Ϊ84MHZ    84000 000 / 8400 = 10000
void TIM14_Init(void)
{
	//1.ʹ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
	
	//2.���ö�ʱ��,��ʼ������
	TIM_TimeBaseInitStruct.TIM_Period  	 	= 10000;	//����ֵ, ������ֵ�����˶�ʱʱ�� 0 ~ 65535
	TIM_TimeBaseInitStruct.TIM_Prescaler 	= 8400-1;   //Ԥ��Ƶ��0 ~ 65535
	TIM_TimeBaseInitStruct.TIM_CounterMode	= TIM_CounterMode_Up; //���ϼ���
	TIM_TimeBaseInit(TIM14, &TIM_TimeBaseInitStruct);
	
	//3.�ö�ʱ��ô����
	TIM_ITConfig(TIM14, TIM_IT_Update, ENABLE);
	
	//4.���ö�ʱ����ͨ��
	NVIC_InitStruct.NVIC_IRQChannel					    = TIM8_TRG_COM_TIM14_IRQn; //�����ж�ͨ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority	= 0x02;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority			= 0x02;
	NVIC_InitStruct.NVIC_IRQChannelCmd					= ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
	//5.ʹ�ܶ�ʱ����ʼ����
	TIM_Cmd(TIM14, ENABLE);	
}

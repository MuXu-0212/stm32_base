#include "sys.h"

static   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
static   TIM_OCInitTypeDef  TIM_OCInitStructure;
static   NVIC_InitTypeDef  NVIC_InitStructure;



//Ӳ����ʱ��---��ʱ��3�ĳ�ʼ��
void TIM3_INIT(void)
{
	//ʹ�ܶ�ʱ��3Ӳ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	//���ö�ʱ��3��Ƶֵ������ֵ��
	TIM_TimeBaseStructure.TIM_Period = (10000/2)-1;     			//����ֵ��0~9999��������ʱʱ��
	TIM_TimeBaseStructure.TIM_Prescaler = 8400-1;		//8400-1+1=8400������8400��Ԥ��Ƶֵ
	//TIM_TimeBaseStructure.TIM_ClockDivision = 0;    					//��F407��֧��	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ����ķ���
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	
	//���ö�ʱ��3�жϵĴ�����ʽ��ʱ�����
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	
	//���ö�ʱ��3���ж����ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	
	//ʹ�ܶ�ʱ��3����
	TIM_Cmd(TIM3, ENABLE);


}

void TIM3_IRQHandler(void)
{
	//�жϱ�־λ
	if(TIM_GetITStatus(TIM3, TIM_IT_Update)==SET)
	{
		PFout(9) ^= 1;
		
		//��ձ�־λ
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
	
}


//�������Ź�
//void TIM3_IRQHandler(void)
//{
//	//�жϱ�־λ
//	if (SET==TIM_GetITStatus(TIM3, TIM_IT_Update))
//	{
//		if(iwdg_flag)
//		{
//			//û500msιһ�ι���CPU����λ
//			IWDG_ReloadCounter();//ˢ�¼���ֵ == ι������ֹ����ֵ����0������λ
//		}
//		//��ձ�־λ
//		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
//	}
//}














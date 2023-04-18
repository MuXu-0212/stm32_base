#include "myhead.h"

static GPIO_InitTypeDef Key_init;
static EXTI_InitTypeDef EXTI_InitStruct;
static NVIC_InitTypeDef NVIC_InitStruct;
	
void EXTI0_Init(void)
{
	//ʹ��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	//ʹ���ж���ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	

	Key_init.GPIO_Pin  	= GPIO_Pin_0;
	Key_init.GPIO_Mode 	= GPIO_Mode_IN;
	Key_init.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	Key_init.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &Key_init);
	
	//�����ǳ�ʼ���õ����� �� �ж��߽�������  ��PA0�����Ž��������ж�
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource0);
	
	
	//�ж�����
	EXTI_InitStruct.EXTI_Line 		= EXTI_Line0;            //ѡ����һ���ж���
	EXTI_InitStruct.EXTI_Mode 		= EXTI_Mode_Interrupt;   //�ж�
	EXTI_InitStruct.EXTI_Trigger	= EXTI_Trigger_Falling;  //�½��ش���
	EXTI_InitStruct.EXTI_LineCmd	= ENABLE;  				 //ʹ�������ж���
	EXTI_Init(&EXTI_InitStruct);
	
	//�����ж�ͨ�����ж����ȼ�
	NVIC_InitStruct.NVIC_IRQChannel						= EXTI0_IRQn;   //ѡ���ж�ͨ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority	= 0x02;  		//��ռ���ȼ� 0~3
	NVIC_InitStruct.NVIC_IRQChannelSubPriority			= 0x02 ;  		//��Ӧ���ȼ� 0~3
	NVIC_InitStruct.NVIC_IRQChannelCmd  				= ENABLE;		//ʹ���ж�ͨ��
	
	NVIC_Init(&NVIC_InitStruct);
	
	//�����ж����ȼ�����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
}

#include "sys.h"

static TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
static TIM_OCInitTypeDef  TIM_OCInitStructure;
//static NVIC_InitTypeDef  NVIC_InitStructure;
static GPIO_InitTypeDef  GPIO_InitStructure;


//��ʱ��14�ĳ�ʼ��
void TIM14_Init(void)
{
	/* GPIOG �ⲿʱ��ʹ�� */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	/* Enable TIM14 clocks */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14 , ENABLE);
	
	/* ����PG9���������ģʽ*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	//��9������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	//���ù���ģʽ�������Ž�������Ӳ���Զ�����
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	//������������������������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//������Ӧ
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	//û��ʹ������������
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	
    //�������붨ʱ��14��������
    GPIO_PinAFConfig(GPIOF,GPIO_PinSource9,GPIO_AF_TIM14);
	
	//���ö�ʱ��14��Ƶֵ������ֵ��
	TIM_TimeBaseStructure.TIM_Period = (10000/100)-1;     //����ֵ��0~99���������Ƶ��Ϊ100Hz
	//TIM_TimeBaseStructure.TIM_Period = (10000/20)-1;     //����ֵ��0~499���������Ƶ��Ϊ20Hz
	TIM_TimeBaseStructure.TIM_Prescaler = 8400-1;		//8400-1+1=8400������8400��Ԥ��Ƶֵ
	//TIM_TimeBaseStructure.TIM_ClockDivision = 0;    					//��F407��֧��	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ����ķ���
	TIM_TimeBaseInit(TIM14, &TIM_TimeBaseStructure);
	
	
//	//���ö�ʱ��3�жϵĴ�����ʽ��ʱ�����
//	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	
//	//���ö�ʱ��3���ж����ȼ�
//	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);


	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;				
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//��/�ر��������
	TIM_OCInitStructure.TIM_Pulse = 50;								//�Ƚ�ֵ����ռ�ձ�, �Ƚ�ֵ=ռ�ձ�*(������ֵ(99)+1)
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       //��Ч״̬Ϊ�ߵ�ƽ������Ч״̬Ϊ�͵�ƽ

	TIM_OC1Init(TIM14, &TIM_OCInitStructure);

	
	//ʹ�ܶ�ʱ��14����
	TIM_Cmd(TIM14, ENABLE);
}


void TIM1_Init(void)
{
	//ʹ�ܶ�ʱ��1Ӳ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);
	/* GPIOG �ⲿʱ��ʹ�� */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
//	/* Enable TIM1 clocks */
//	RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);
	
	/* ����PG9���������ģʽ*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	//��9������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	//���ù���ģʽ�������Ž�������Ӳ���Զ�����
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	//������������������������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//������Ӧ
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	//û��ʹ������������
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	
    //�������붨ʱ��1��������
    GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_TIM1);
	
	//���ö�ʱ��1��Ƶֵ������ֵ��
	//��ʱ��1Ӳ��ʱ��Ƶ��=(84MHz * 2)/TIM_Prescaler(16800) = 10000Hz
	TIM_TimeBaseStructure.TIM_Period = (10000/100)-1;     //����ֵ��0~99���������Ƶ��Ϊ100Hz
	//TIM_TimeBaseStructure.TIM_Period = (10000/20)-1;     //����ֵ��0~499���������Ƶ��Ϊ20Hz
	TIM_TimeBaseStructure.TIM_Prescaler = 16800-1;		//8400-1+1=8400������8400��Ԥ��Ƶֵ
	//TIM_TimeBaseStructure.TIM_ClockDivision = 0;    					//��F407��֧��	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ����ķ���
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;				
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//��/�ر��������
	TIM_OCInitStructure.TIM_Pulse = 100;								//�Ƚ�ֵ����ռ�ձ�, �Ƚ�ֵ=ռ�ձ�*(������ֵ(99)+1)
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       //��Ч״̬Ϊ�ߵ�ƽ������Ч״̬Ϊ�͵�ƽ

	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	
	//ʹ�ܶ�ʱ��1����
	TIM_Cmd(TIM1, ENABLE);
	
	
	//����PWM�������
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
}









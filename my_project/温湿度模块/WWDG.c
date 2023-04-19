#include "sys.h"


static NVIC_InitTypeDef NVIC_InitStruct;

//���ڿ��Ź���ʼ��
void WWDG_Init(void)
{
	//ʹ�ܴ��ڿ��Ź���ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
	
	//����Ԥ��Ƶ ���ǵ�WWDG����Ƶ��Ϊ 42Mhz
	//WWDG_Prescaler_8: WWDG counter clock = (PCLK1/4096)/8 = 1281HZ
	WWDG_SetPrescaler(WWDG_Prescaler_8);
	
	//���ô��ڿ��Ź�������ֵ ȡֵ��Χ������ 64 ~ 127  ����49 ����36.6 
	// 64 ~ 80֮�����һ����Чι��  ��һ����Ϊ 780us * ��127 - 80��
	WWDG_SetWindowValue(80);
	
	//���ü���ֵ������,��ʹ�ܿ��Ž��й���
	WWDG_Enable(127);
}

void WWDG_Exti_Init(void)
{
	//ʹ�ܴ��ڿ��Ź���ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);

	//���ô��ڿ��Ź���Ƶ,��ƵֵԽ��,����ʱ��Խ��
	//WWDG counter clock = (PCLK1/4096)/8
	//����Ƶ��: 42Mhz / 4096 / 8 = 1281Hz  
	//�����ڵ�һ������Ƶ�� Ҳ������ζ��1����1281����
	//�Ǽ�һ������Ϊ 1000ms / 1281 = 0.7806 1us �� 780.6 ����
	WWDG_SetPrescaler(WWDG_Prescaler_8);
	
	//����ʱ�䴰�ڵ�����ֵ
	WWDG_SetWindowValue(80);
	
	//ʹ����ǰ�����ж�
    WWDG_EnableIT();
	//���ڿ��Ź��ж����ȼ�����
    NVIC_InitStruct.NVIC_IRQChannel		  			  = WWDG_IRQn;	//�����ж�ͨ��
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x01;       //������Ӧ���ȼ�
    NVIC_InitStruct.NVIC_IRQChannelSubPriority	  	  = 0x02;	//������ռ���ȼ�
    NVIC_InitStruct.NVIC_IRQChannelCmd		  		  = ENABLE;     //ʹ�ܹ���
    NVIC_Init(&NVIC_InitStruct);
	
	//���ü���ֵ����ʹ�ܴ��ڿ��Ź�����
	WWDG_Enable(127);
 }


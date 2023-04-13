#include "stm32f4xx.h"


static GPIO_InitTypeDef GPIO_InitStructure;

void delay(void)
{
	uint32_t i = 0x2000000;
	while(i--);
}

int main(void)
{
	//led1:PF9	led2:PF10	led3:PE13	led4:PE14
	//ʹ�ܣ��򿪣��˿�F��Ӳ��ʱ�ӣ����ǶԶ˿�F����
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	//��ʼ������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;	//��9�� 10������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	//���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	//��������������������������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//������Ӧ
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	//û��ʹ������������
	GPIO_Init(GPIOF,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;	//��13��14������
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	
	//����LEDϨ��
	GPIO_SetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);
	GPIO_SetBits(GPIOE,GPIO_Pin_13 | GPIO_Pin_14);
	
	while(1)
	{
		//PF9��������͵�ƽ
		GPIO_ResetBits(GPIOF,GPIO_Pin_9);
		delay();
		
		//PF9��������ߵ�ƽ
		GPIO_SetBits(GPIOF,GPIO_Pin_9);
		delay();

		GPIO_ResetBits(GPIOF,GPIO_Pin_10);
		delay();
		
		GPIO_SetBits(GPIOF,GPIO_Pin_10);
		delay();
		
		GPIO_ResetBits(GPIOE,GPIO_Pin_13);
		delay();
		
		GPIO_SetBits(GPIOE,GPIO_Pin_13);
		delay();

		GPIO_ResetBits(GPIOE,GPIO_Pin_14);
		delay();
		
		GPIO_SetBits(GPIOE,GPIO_Pin_14);
		delay();
	}

}




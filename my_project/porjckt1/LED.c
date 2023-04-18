#include "myhead.h"

static GPIO_InitTypeDef gpio_init;

void LCD_Init(void)
{
	//ͬһ�����ţ�����ʹ�� | �Ž�������
	//1.ʹ�ܣ��򿪣�ʱ��    A���߼� H������ B:����    ���ж�PF��˿ڹ���
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	//2.��������
	gpio_init.GPIO_Pin  	= GPIO_Pin_9 | GPIO_Pin_10;   	//��ʼ��PF9������
	gpio_init.GPIO_Mode 	= GPIO_Mode_OUT;	//��������Ϊ���ģʽ
	gpio_init.GPIO_Speed	= GPIO_High_Speed;  //����Ϊ������Ӧ 100Mhz
	gpio_init.GPIO_OType    = GPIO_OType_PP;    //�������,�������
	gpio_init.GPIO_PuPd     = GPIO_PuPd_NOPULL; //����ģʽ �Ȳ�����Ҳ������
		
	GPIO_Init(GPIOF,&gpio_init);
	
	
		//2.��������
	gpio_init.GPIO_Pin  	= GPIO_Pin_13 | GPIO_Pin_14;   	//��ʼ��PF9������
	gpio_init.GPIO_Mode 	= GPIO_Mode_OUT;	//��������Ϊ���ģʽ
	gpio_init.GPIO_Speed	= GPIO_High_Speed;  //����Ϊ������Ӧ 100Mhz
	gpio_init.GPIO_OType    = GPIO_OType_PP;    //�������,�������
	gpio_init.GPIO_PuPd     = GPIO_PuPd_NOPULL; //����ģʽ �Ȳ�����Ҳ������
	GPIO_Init(GPIOE,&gpio_init);
	
	PFout(9) = 1;
	PFout(10) = 1;
	PEout(13) = 1;
	PEout(14) = 1;
	
}

#include "sys.h"

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


int32_t  delay_ms(uint32_t nms)
{
	uint32_t t = nms;
	uint32_t temp;

	while(t--)
	{
		SysTick->CTRL = 0;
		SysTick->LOAD = 21000-1;
		SysTick->VAL = 0; 
		SysTick->CTRL = 1;             
		while(1)
		{

			temp=SysTick->CTRL;
			//���count flag
			if(temp & 0x00010000)
			{
				break;    
			}
			//���ϵͳ��ʱ���Ƿ�����ر�    
			if((temp & 0x1)==0)
			{
				 return -1;              
			}
		}
	}    

	SysTick->CTRL = 0;     
	return 0;
}


int32_t delay_us(uint32_t nus)
{
	uint32_t temp;

	SysTick->CTRL = 0;                     
	SysTick->LOAD = (nus*21)-1;         
	SysTick->VAL = 0;                     
	SysTick->CTRL = 1;                     

	while(1)
	{
		temp=SysTick->CTRL;
		//���count flag
		if(temp & 0x00010000)
		{
				break;
		}
		//���ϵͳ��ʱ���Ƿ�����ر�    
		if((temp & 0x1)==0)
		{
			return -1;    
		}
	}

	SysTick->CTRL = 0; 
	return 0;
}


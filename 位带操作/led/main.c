#include "stm32f4xx.h"
#include "head.h"

static GPIO_InitTypeDef GPIO_InitStructure;

void delay(void)
{
	uint32_t i = 0x2000000;
	while(i--);
}

void delay2(void)
{
	uint32_t i = 0x2000;
	while(i--);
}

int main(void)
{
	
	volatile uint32_t* peout[2];
	volatile uint32_t* pfout[2];
	volatile uint32_t* s1;
	volatile uint32_t* s2;
	
	
	//led1:PF9	led2:PF10	led3:PE13	led4:PE14
	//ʹ�ܣ��򿪣��˿�F��Ӳ��ʱ�ӣ����ǶԶ˿�F����
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	//��ʼ������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;	//��9�� 10������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	//���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	//��������������������������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//������Ӧ
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	//û��ʹ������������
	GPIO_Init(GPIOF,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;	//��13��14������
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	
	//��ʼ������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	//0������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;	//���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	//��������������������������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//������Ӧ
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	//û��ʹ������������
	GPIO_Init(GPIOF,&GPIO_InitStructure);
	

	//��ʼ������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	//2������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;	//���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	//��������������������������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//������Ӧ
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	//û��ʹ������������
	GPIO_Init(GPIOE2,&GPIO_InitStructure);

	
	//����LEDϨ��
	//GPIO_SetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);
	//GPIO_SetBits(GPIOE,GPIO_Pin_13 | GPIO_Pin_14);
	
	//����LEDȫ��������һ��
	//GPIO_ResetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);
	//GPIO_ResetBits(GPIOE,GPIO_Pin_13 | GPIO_Pin_14);

/*
	//����LEDȫ������������
	GPIO_ResetBits(GPIOF,GPIO_Pin_9);
	GPIO_ResetBits(GPIOF,GPIO_Pin_10);
	GPIO_ResetBits(GPIOE,GPIO_Pin_13);
	GPIO_ResetBits(GPIOE,GPIO_Pin_14);
	delay();
	*/
	

	peout[0] = &(PEout(13));
	peout[1] = &(PEout(14));
	pfout[0] = &(PFout(9));
	pfout[1] = &(PFout(10));

	s1 = &(PAin(0));
	s2 = &(PEin(2));
	
	*peout[0] = 1;
	*peout[1] = 1;
	*pfout[0] = 1;
	*pfout[1] = 1;

	while(1)
	{
		if(*s1 == 0)
		{
			delay2();
			if(s1 == 0)
			{
					*peout[0] = 0;
					*peout[1] = 0;
					*pfout[0] = 0;
					*pfout[1] = 0;
				
					*pfout[0] = 1;	//pf9��
					delay();
					
					*pfout[0] = 0;	//pf9��
					*pfout[1] = 1;	//pf10��
					delay();
					
					*pfout[1] = 0;	//pf10��
					*peout[0] = 1;	//pe13��
					delay();
					
					*peout[0] = 0;	//pe13��
					*peout[1] = 1;	//pe14��
					delay();
					
					*peout[1] = 0;	//pe14��
				
			}
		}
		if(*s2 == 0)
		{
			delay2();
			if(*s2 == 0)
			{
				*peout[0] = 0;
				*peout[1] = 0;
				*pfout[0] = 0;
				*pfout[1] = 0;
				delay();
				delay();
				delay();
				delay();
				delay();
				delay();
			}
		}
	}

	
	

	
/*
	while(1)
	{
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == Bit_RESET)
		{
			GPIO_ResetBits(GPIOF, GPIO_Pin_9);
		}
		else
		{
			GPIO_SetBits(GPIOF,GPIO_Pin_9);
		}
	}
	*/
	
	
//	while(1);
	
	/*
	while(1)
	{
		//PF9��������͵�ƽ
		GPIO_SetBits(GPIOF,GPIO_Pin_9);
		delay();
		
		GPIO_ResetBits(GPIOF,GPIO_Pin_9);
		GPIO_SetBits(GPIOF,GPIO_Pin_10);
		delay();
		
		GPIO_ResetBits(GPIOF,GPIO_Pin_10);
		GPIO_SetBits(GPIOE,GPIO_Pin_13);
		delay();
		
		GPIO_ResetBits(GPIOE,GPIO_Pin_13);
		GPIO_SetBits(GPIOE,GPIO_Pin_14);
		delay();
		
		GPIO_ResetBits(GPIOE,GPIO_Pin_14);
	}
	*/

}




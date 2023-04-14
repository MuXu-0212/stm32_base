#include "stm32f4xx.h"
#include "head.h"

static GPIO_InitTypeDef GPIO_InitStructure;

void delay(void)
{
	uint32_t i = 0x2000000;
	while(i--);
}

int main(void)
{
	uint32_t* peout[2];
	uint32_t* pfout[2];
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
	

	*peout[0] = PEout(13);
	*peout[1] = PEout(14);
	*pfout[0] = PFout(9);
	*pfout[1] = PFout(10);

/*
	//����LEDȫ��
	*pfout[0] = 0;	//pf9
	*pfout[1] = 0;	//pf10
	*peout[0] = 0;	//pe13
	*peout[1] = 0;	//pe14
	*/
	
	while(1)
	{
		
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
	
/*
	while(1)
	{
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == Bit_RESET)
		{
			GPIO_ResetBits(GPIOF, GPIO_Pin_9);
		}
		else
		{
			GPIO_SetBits(GPIO_BSRR_BR_0,GPIOA_Pin_9);
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




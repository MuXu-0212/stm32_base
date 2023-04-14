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
	//使能（打开）端口F的硬件时钟，就是对端口F供电
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	

	//初始化引脚
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;	//第9、 10根引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	//输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	//推挽输出，增加输出电流的能力
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//高速相应
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	//没有使能上下拉电阻
	GPIO_Init(GPIOF,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;	//第13、14根引脚
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	
	//所有LED熄灭
	//GPIO_SetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);
	//GPIO_SetBits(GPIOE,GPIO_Pin_13 | GPIO_Pin_14);
	
	//所有LED全亮（方法一）
	//GPIO_ResetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);
	//GPIO_ResetBits(GPIOE,GPIO_Pin_13 | GPIO_Pin_14);

/*
	//所有LED全亮（方法二）
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
	//所有LED全亮
	*pfout[0] = 0;	//pf9
	*pfout[1] = 0;	//pf10
	*peout[0] = 0;	//pe13
	*peout[1] = 0;	//pe14
	*/
	
	while(1)
	{
		
		*pfout[0] = 1;	//pf9灭
		delay();
		
		*pfout[0] = 0;	//pf9亮
		*pfout[1] = 1;	//pf10灭
		delay();
		
		*pfout[1] = 0;	//pf10亮
		*peout[0] = 1;	//pe13灭
		delay();
		
		*peout[0] = 0;	//pe13亮
		*peout[1] = 1;	//pe14灭
		delay();
		
		*peout[1] = 0;	//pe14亮
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
		//PF9引脚输出低电平
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




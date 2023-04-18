#include "myhead.h"

static GPIO_InitTypeDef gpio_init;

void LCD_Init(void)
{
	//同一组引脚，可以使用 | 号进行连接
	//1.使能（打开）时钟    A：高级 H：高速 B:总线    进行对PF组端口供电
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	//2.配置引脚
	gpio_init.GPIO_Pin  	= GPIO_Pin_9 | GPIO_Pin_10;   	//初始化PF9号引脚
	gpio_init.GPIO_Mode 	= GPIO_Mode_OUT;	//配置引脚为输出模式
	gpio_init.GPIO_Speed	= GPIO_High_Speed;  //配置为高速响应 100Mhz
	gpio_init.GPIO_OType    = GPIO_OType_PP;    //推挽输出,增大电流
	gpio_init.GPIO_PuPd     = GPIO_PuPd_NOPULL; //浮空模式 既不上拉也不下拉
		
	GPIO_Init(GPIOF,&gpio_init);
	
	
		//2.配置引脚
	gpio_init.GPIO_Pin  	= GPIO_Pin_13 | GPIO_Pin_14;   	//初始化PF9号引脚
	gpio_init.GPIO_Mode 	= GPIO_Mode_OUT;	//配置引脚为输出模式
	gpio_init.GPIO_Speed	= GPIO_High_Speed;  //配置为高速响应 100Mhz
	gpio_init.GPIO_OType    = GPIO_OType_PP;    //推挽输出,增大电流
	gpio_init.GPIO_PuPd     = GPIO_PuPd_NOPULL; //浮空模式 既不上拉也不下拉
	GPIO_Init(GPIOE,&gpio_init);
	
	PFout(9) = 1;
	PFout(10) = 1;
	PEout(13) = 1;
	PEout(14) = 1;
	
}

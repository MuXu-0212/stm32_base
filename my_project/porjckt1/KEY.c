#include "myhead.h"


static GPIO_InitTypeDef Key_init;

void KEY_Init(void)
{
	// πƒ‹ ±÷”
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	Key_init.GPIO_Pin   = GPIO_Pin_0;
	Key_init.GPIO_Mode  = GPIO_Mode_IN;
	Key_init.GPIO_Speed = GPIO_Speed_100MHz;
	Key_init.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOA,&Key_init);
}



#include "sys.h"

void WWDG_Init(void)
{
	//使能窗口看门狗硬件时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
	
	//设置分频值
	//窗口看门狗的硬件时钟=(PCLK/4096)/8=42MHz/4096/8=1281Hz
	//
	WWDG_SetPrescaler(WWDG_Prescaler_8);
	
	//设置时间窗口的上限值
	WWDG_SetWindowValue(80);
	
	//设置计数值
	WWDG_Enable(127);
	
}



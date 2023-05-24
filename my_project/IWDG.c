#include "sys.h"

void IWDG_Init(void)
{
	//允许访问独立看门狗
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	
	//配置独立看门狗的分频值为256
	//独立看门狗的硬件时钟=32KHz/256=125Hz
	IWDG_SetPrescaler(IWDG_Prescaler_256);
	
	//设置独立看门狗的计数值
	//计数范围：0~124，共进行125次计数，就是1秒时间的到达
	//125是1秒，250是2秒
	IWDG_SetReload(125-1);

//	//重载计数值==刷新计数值
	IWDG_ReloadCounter();
	
	//使能独立看门狗工作
	IWDG_Enable();
}





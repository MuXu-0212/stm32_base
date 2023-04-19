#include "sys.h"

void IWDG_Init(void)
{
	//允许写访问独立看门狗
	//因为看门狗是一个很重要的硬件，只有授权写权限时，才能进行操作
	//默认为没有写权限，所以需要调用此函数，授予写权限，才能访问独立看门狗
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	
	//配置独立看门狗的运行频率 分频越大 定时时间越长
	//32Khz 32000 / 256 = 125Hz 	
	IWDG_SetPrescaler(IWDG_Prescaler_256);
	
	//设置喂狗的计数值  取值范围不能够超过 4095 == 设置看门狗的上限值
	//计数值确定了定时时长 因为上面的工作频率为125HZ 也就是1秒数125个数。
	//此时是为独立看门狗设置定时时间,也是设定独立看门狗的上限值
	IWDG_SetReload(125-1);
	
	//重加载计数值 == 刷新计数值 == 喂狗
	IWDG_ReloadCounter();
	
	//使能独立看门狗
	IWDG_Enable();
	
}

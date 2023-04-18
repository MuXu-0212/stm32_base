#include "myhead.h"



//工作在21Mhz  也就是一秒计数21 000 000
void delay_ms(uint32_t n)
{
	while(n--)
	{
		SysTick->CTRL = 0;                        // Disable SysTick    关闭系统定时器,关闭后才可以去配置系统计数值
		SysTick->LOAD = 21000-1;                  // Count from 255 to 0 (256 cycles)   配置计数值
		SysTick->VAL  = 0;                        // Clear current value as well as count flag  清除当前值和计数标志
		SysTick->CTRL = 1;                        // Enable SysTick timer with processor clock  启用SysTick计时器与处理器时钟
		while ((SysTick->CTRL & 0x00010000)==0);  // Wait until count flag is set   等待直到计数标志被设置
		
	}
	SysTick->CTRL = 0;                        // Disable SysTick   禁用SysTick定时器
}





int main(void)
{
	LCD_Init();

	
	//168000000 / 100 =  10ms 产生一次中断
	//168000000 / 1000 =  1ms 产生一次中断
	//168000000 / 10000 =  100us 产生一次中断
	//168000000 / 100000 =  10us 产生一次中断
	//168000000 / 1000000 =  1us 产生一次中断
	//SysTick_Config(SystemCoreClock/100);
	
	
	
	while(1)
	{
		delay_ms(500);
		PFout(9) ^= 1;
	}
}


//void SysTick_Handler(void)
//{
//	static uint32_t i = 0;
//	i++;
//	if(i >= 5)
//	{
//		i = 0;
//		PFout(9) ^= 1;   //0 ^ 1 = 1 1 ^ 1 = 0
//	}
//}
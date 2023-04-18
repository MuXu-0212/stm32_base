#include "myhead.h"



//������21Mhz  Ҳ����һ�����21 000 000
void delay_ms(uint32_t n)
{
	while(n--)
	{
		SysTick->CTRL = 0;                        // Disable SysTick    �ر�ϵͳ��ʱ��,�رպ�ſ���ȥ����ϵͳ����ֵ
		SysTick->LOAD = 21000-1;                  // Count from 255 to 0 (256 cycles)   ���ü���ֵ
		SysTick->VAL  = 0;                        // Clear current value as well as count flag  �����ǰֵ�ͼ�����־
		SysTick->CTRL = 1;                        // Enable SysTick timer with processor clock  ����SysTick��ʱ���봦����ʱ��
		while ((SysTick->CTRL & 0x00010000)==0);  // Wait until count flag is set   �ȴ�ֱ��������־������
		
	}
	SysTick->CTRL = 0;                        // Disable SysTick   ����SysTick��ʱ��
}





int main(void)
{
	LCD_Init();

	
	//168000000 / 100 =  10ms ����һ���ж�
	//168000000 / 1000 =  1ms ����һ���ж�
	//168000000 / 10000 =  100us ����һ���ж�
	//168000000 / 100000 =  10us ����һ���ж�
	//168000000 / 1000000 =  1us ����һ���ж�
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
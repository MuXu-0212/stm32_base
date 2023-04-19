#include "sys.h"
#include <stdio.h>

struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, ch);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    return ch;
}


int main(void)
{
	uint8_t p[5];
	Usart1_Init(115200);
	
	DHT11_Init();
	while(1)
	{
		DHT11_Read_Data( p);
		printf("湿度为:%d.%d 温度为%d.%d\r\n", p[1], p[0], p[3], p[2]);
		delay_ms(500);
		delay_ms(500);
		delay_ms(500);
	}
	/*
	
	WWDG_Exti_Init();
	
	if(RCC_GetFlagStatus(RCC_FLAG_WWDGRST) == SET)
	{
		printf("Wwdg rest cpu\r\n");
	}
	else
	{
		printf("kye rest cpu\r\n");
	}
	
	RCC_ClearFlag();
	
	
	printf("This is iwdg test\r\n");
	while(1);
	
	
//	return 0;

}


void WWDG_IRQHandler(void)
{
	 if(WWDG_GetFlagStatus() == SET)
	 {
        //执行喂狗动作
        WWDG_SetCounter(127);
        //清空提前唤醒中断标志位
        WWDG_ClearFlag();
	 }
	 */
}

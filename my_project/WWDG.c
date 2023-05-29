#include "sys.h"

void WWDG_Init(void)
{
	//ʹ�ܴ��ڿ��Ź�Ӳ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
	
	//���÷�Ƶֵ
	//���ڿ��Ź���Ӳ��ʱ��=(PCLK/4096)/8=42MHz/4096/8=1281Hz
	//
	WWDG_SetPrescaler(WWDG_Prescaler_8);
	
	//����ʱ�䴰�ڵ�����ֵ
	WWDG_SetWindowValue(80);
	
	//���ü���ֵ
	WWDG_Enable(127);
	
}



#include "sys.h"

void IWDG_Init(void)
{
	//������ʶ������Ź�
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	
	//���ö������Ź��ķ�ƵֵΪ256
	//�������Ź���Ӳ��ʱ��=32KHz/256=125Hz
	IWDG_SetPrescaler(IWDG_Prescaler_256);
	
	//���ö������Ź��ļ���ֵ
	//������Χ��0~124��������125�μ���������1��ʱ��ĵ���
	//125��1�룬250��2��
	IWDG_SetReload(125-1);

//	//���ؼ���ֵ==ˢ�¼���ֵ
	IWDG_ReloadCounter();
	
	//ʹ�ܶ������Ź�����
	IWDG_Enable();
}





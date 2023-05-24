#include "sys.h"

static EXTI_InitTypeDef   EXTI_InitStructure;
static GPIO_InitTypeDef   GPIO_InitStructure;
static NVIC_InitTypeDef   NVIC_InitStructure;


//�ⲿ�жϳ�ʼ��
void EXTILine0_Init(void)
{
	/* Enable GPIOA clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	/* Enable SYSCFG clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* Configure PA0 pin as input floating */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Connect EXTI Line0 to PA0 pin */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

	/* Configure EXTI Line0 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;				//�ⲿ�ж�0
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		//�ж�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  //�½��ش���������ʶ�𰴼��İ���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//ʹ��
	EXTI_Init(&EXTI_InitStructure);

	/* Enable and set EXTI Line0 Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//�ⲿ�ж�0������ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;       //��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //ʹ�ܸ�ͨ��
	NVIC_Init(&NVIC_InitStructure);
	
	//RESETΪ0
	GPIO_SetBits( GPIOF, GPIO_Pin_9 | GPIO_Pin_10);
	GPIO_ResetBits( GPIOE, GPIO_Pin_13 | GPIO_Pin_14);
	
}
 



//�жϷ���interrupt serve source
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) == SET)
	{

		/* function */
		//PFout(9) = 0;
		GPIOF->ODR ^= GPIO_Pin_9;
		GPIOF->ODR ^= GPIO_Pin_10;
		GPIOE->ODR ^= GPIO_Pin_13;
		GPIOE->ODR ^= GPIO_Pin_14;

		 /* Clear the EXTI line 0 pending bit */
		EXTI_ClearITPendingBit(EXTI_Line0);

	}

}


void SYS_TIMER(void)
{
	//ϵͳ��ʱ����ʱ��Դ168MHz
	//ֻҪϵͳ��ʱ������168 00 0000���������ʹ���1����ʱ��ĵ���
	//ֻҪϵͳ��ʱ������168 00 0000/10���������ʹ���1/10����ʱ��ĵ���
	//ֻҪϵͳ��ʱ������168 00 0000/100���������ʹ���1/100���ӵĵ���
#if 0
	//����ϵͳ��ʱ������1000Hz���ж�
	//����ʱ��T=1/f=1/10Hz=100ms
	SysTick_Config(SystemCoreClock / 10);
	//�Ʋ�������ʱ�䲻׼ȷ��ԭ��16800 0000/10=1680 0000,�����˼�����2^24=1677 7216�ķ�Χ
#endif

#if 0
	//����ϵͳ��ʱ������1000Hz���ж�
	//����ʱ��T=1/f=1/10Hz=1ms
	SysTick_Config(SystemCoreClock / 1000);
#endif

#if 0
	//����ϵͳ��ʱ������1000Hz���ж�
	//����ʱ��T=1/f=1=1s
	SysTick_Config(SystemCoreClock);
#endif
}

//ϵͳ��ʱ��
//void SysTick_Handler(void)
//{
//	static uint32_t i=0; 
//	static uint32_t j=0; 
//	static uint32_t k=0; 
//	static uint32_t h=0;
//	
//	i++;
//	j++;
//	k++;
//	h++;
//	if(i>=100)
//	{
//		i=0;
//		//��״̬�ķ�ת
//		PFout(9)^=1;	//1^0=1		1^1=0	0^1=1	1^1=0
//	}
//	if(j>=330)
//	{
//		j=0;
//		PFout(10)^=1;
//	}
//	if(k>=1500)
//	{
//		k=0;
//		PEout(13)^=1;
//	}
//	if(h>=2200)
//	{
//		h=0;
//		PEout(14)^=1;
//	}
//}

/*
//���붨ʱ����ʱ
void delay_ms(uint32_t n)
{
#if 0
	while(n--)
	{
		SysTick->CTRL = 0; // Disable SysTick
		SysTick->LOAD = (168000)-1; // Count from 255 to 0 (256 cycles)
		SysTick->VAL = 0; // Clear current value as well as count flag
		SysTick->CTRL = 5; // Enable SysTick timer with processor clock
		while ((SysTick->CTRL & 0x00010000)==0);// Wait until count flag is set
	}
	SysTick->CTRL = 0; // Disable SysTick
#endif
	
#if 0
	//��ϵͳʹ��ʱ�ӵİ˷�Ƶ�����ʱ��ϵͳ��ʱ����ʱ��Դ=168MHz/8=21MHz
	//ֻҪ����2100 0000���������ʹ���1����ʱ��ĵ���
	//ֻҪ2100 0000���������ʹ���1/1000����ʱ��ĵ���
	while(n--)
	{
		SysTick->CTRL = 0; // Disable SysTick
		SysTick->LOAD = (21000)-1; // Count from 255 to 0 (256 cycles) ���ü���ֵ(21000)-1 ~ 0
		SysTick->VAL = 0; // Clear current value as well as count flag
		SysTick->CTRL = 1; // Enable SysTick timer with processor clock
		while ((SysTick->CTRL & 0x00010000)==0);// Wait until count flag is set
	}
	SysTick->CTRL = 0; // Disable SysTick	
#endif
}
*/

//���붨ʱ����ʱ
#if 1
uint32_t delay_ms(uint32_t n)
{
	while(n--)
	{
		SysTick->CTRL = 0; 				// Disable SysTick���ر�ϵͳ��ʱ��
		SysTick->LOAD = (168000)-1; 	// ���ü���ֵ(168000)-1 ~ 0
		SysTick->VAL  = 0; 		// Clear current value as well as count flag
		SysTick->CTRL = 5; 		// Enable SysTick timer with processor clock
		while ((SysTick->CTRL & 0x10000)==0);// Wait until count flag is set
	}
	
	SysTick->CTRL = 0; 		// Disable SysTick	
	
	

//	uint32_t temp;
//	SysTick->LOAD = n * 22500;	//��������Ҫ�ݼ�
//	SysTick->VAL = 0;	//����������
//	SysTick->CTRL |=1;	//����������
//    
//	//�ȴ��������е���ֵ������0
//	do{
//		temp = SysTick->CTRL;
//	}while( !(temp & (1<<16)) && (temp&0x01) );
//	//����д��������Ϊ�Ĵ���Ϊ0ʱҪ����ѭ����
//	//�������ж�ʱ��ctrl�Ĵ����ĵ�0bit��ǿ����Ϊ0
//	
//	SysTick->CTRL &= ~1;	//�رռ�����
	return 0;
}
#endif

//΢�붨ʱ����ʱ
uint32_t delay_us(uint32_t n)
{

	SysTick->CTRL = 0; // Disable SysTick
	SysTick->LOAD = (168*n)-1; // Count from 255 to 0 (256 cycles)
	SysTick->VAL = 0; // Clear current value as well as count flag
	SysTick->CTRL = 5; //0101 Enable SysTick timer with processor clock
	while ((SysTick->CTRL & 0x00010000)==0);// Wait until count flag is set
	SysTick->CTRL = 0; // Disable SysTick
	
	
//	uint32_t temp;

//	SysTick->CTRL = 0;                     
//	SysTick->LOAD = (n*21)-1;         
//	SysTick->VAL = 0;                     
//	SysTick->CTRL = 1;                     

//	while(1)
//	{
//		temp=SysTick->CTRL;
//		//���count flag
//		if(temp & 0x00010000)
//		{
//				break;
//		}
//		//���ϵͳ��ʱ���Ƿ�����ر�    
//		if((temp & 0x1)==0)
//		{
//			return -1;    
//		}
//	}

//	SysTick->CTRL = 0; 
	return 0;
	
	
}





#include "sys.h"

//static GPIO_InitTypeDef  GPIO_InitStructure;
//static USART_InitTypeDef USART_InitStructure;
static NVIC_InitTypeDef NVIC_InitStructure;

static RTC_TimeTypeDef  RTC_TimeStructure;
static RTC_InitTypeDef  RTC_InitStructure;
static RTC_DateTypeDef  RTC_DateStructure;
//static RTC_AlarmTypeDef RTC_AlarmStructure;

static NVIC_InitTypeDef  NVIC_InitStructure;
static EXTI_InitTypeDef  EXTI_InitStructure;
//static u32 g_rtc_wakeup_event;


void rtc_init(void)
{
	/* Enable the PWR clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

	/* Allow access to RTC */
	PWR_BackupAccessCmd(ENABLE);
	
	//ʹ��LSE��ʱ��
	RCC_LSEConfig(RCC_LSE_ON);
	
	/* Wait till LSE is ready �ȴ��ⲿ����������ٷ�����Ҫ��ӳ�ʱ����*/  
	while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
	{
	}
	
	/* Select the RTC Clock Source */ //ѡ��LSE��ΪRTC���ⲿ��ʱ��Դ
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

	/* Enable the RTC Clock ,ʹ��RTC��Ӳ��ʱ��*/
	RCC_RTCCLKCmd(ENABLE);
	
	/* Wait for RTC APB registers synchronisation */
	//�ȴ��Ĵ�������
	RTC_WaitForSynchro();
	
	/* ck_spre(1Hz) = RTCCLK(LSE) /(uwAsynchPrediv + 1)/(uwSynchPrediv + 1)*/
	//				= 32768		/ 	128				/	256
	//				= 1Hz
	/* Configure the RTC data register and RTC prescaler */
	RTC_InitStructure.RTC_AsynchPrediv = 0x7f;	//�첽��Ƶ
	RTC_InitStructure.RTC_SynchPrediv = 0xff;	//ͬ����Ƶ
	RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;	//24Сʱ��ʽ
	RTC_Init(&RTC_InitStructure);

	/* Set the date: Friday May 12th 2023 */
	RTC_DateStructure.RTC_Year = 0x23;
	RTC_DateStructure.RTC_Month = RTC_Month_May;
	RTC_DateStructure.RTC_Date = 0x12;
	RTC_DateStructure.RTC_WeekDay = RTC_Weekday_Friday;
	RTC_SetDate(RTC_Format_BCD, &RTC_DateStructure);
	
	/* Set the time to 05h 20mn 00s AM */
	RTC_TimeStructure.RTC_H12     = RTC_H12_PM;
	RTC_TimeStructure.RTC_Hours   = 0x14;
	RTC_TimeStructure.RTC_Minutes = 0x55;
	RTC_TimeStructure.RTC_Seconds = 0x00; 
	
	RTC_SetTime(RTC_Format_BCD, &RTC_TimeStructure);   

	/* Indicator for the RTC configuration���ݼĴ��� */
	//RTC_WriteBackupRegister(RTC_BKP_DR0, 0x32F2);
	
	//�رջ��ѹ���
	RTC_WakeUpCmd(DISABLE);

	//Ϊ���ѹ���ѡ��RTC���úõ�ʱ��Դ
	RTC_WakeUpClockConfig(RTC_WakeUpClock_CK_SPRE_16bits);

	//���û��Ѽ���ֵΪ�Զ����أ�д��ֵĬ����0
	RTC_SetWakeUpCounter(1-1);

	//���RTC�����жϱ�־
	RTC_ClearITPendingBit(RTC_IT_WUT);

	//ʹ��RTC�����ж�
	RTC_ITConfig(RTC_IT_WUT,ENABLE);

	//ʹ�ܻ��ѹ���
	RTC_WakeUpCmd(ENABLE);

/* RTC Alarm A Interrupt Configuration */
   /* EXTI configuration *******************************************************/
	EXTI_ClearITPendingBit(EXTI_Line22);
	EXTI_InitStructure.EXTI_Line = EXTI_Line22;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* Enable the RTC Alarm Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = RTC_WKUP_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

void rtc_reinit(void)
{
	/* Enable the PWR clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

	/* Allow access to RTC */
	PWR_BackupAccessCmd(ENABLE);
	
	//ʹ��LSE��ʱ��
	RCC_LSEConfig(RCC_LSE_ON);
	
	/* Wait till LSE is ready �ȴ��ⲿ����������ٷ�����Ҫ��ӳ�ʱ����*/  
	while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
	{
	}
	
	/* Select the RTC Clock Source */ //ѡ��LSE��ΪRTC���ⲿ��ʱ��Դ
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

	/* Enable the RTC Clock ,ʹ��RTC��Ӳ��ʱ��*/
	RCC_RTCCLKCmd(ENABLE);
	
	/* Wait for RTC APB registers synchronisation */
	//�ȴ��Ĵ�������
	RTC_WaitForSynchro();
	
	/* ck_spre(1Hz) = RTCCLK(LSE) /(uwAsynchPrediv + 1)/(uwSynchPrediv + 1)*/
	//				= 32768		/ 	128				/	256
	//				= 1Hz
	/* Configure the RTC data register and RTC prescaler */
//	RTC_InitStructure.RTC_AsynchPrediv = 0x7f;	//�첽��Ƶ
//	RTC_InitStructure.RTC_SynchPrediv = 0xff;	//ͬ����Ƶ
//	RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;	//24Сʱ��ʽ
//	RTC_Init(&RTC_InitStructure);

//	/* Set the date: Friday May 12th 2023 */
//	RTC_DateStructure.RTC_Year = 0x23;
//	RTC_DateStructure.RTC_Month = RTC_Month_May;
//	RTC_DateStructure.RTC_Date = 0x12;
//	RTC_DateStructure.RTC_WeekDay = RTC_Weekday_Friday;
//	RTC_SetDate(RTC_Format_BCD, &RTC_DateStructure);
//	
//	/* Set the time to 05h 20mn 00s AM */
//	RTC_TimeStructure.RTC_H12     = RTC_H12_PM;
//	RTC_TimeStructure.RTC_Hours   = 0x14;
//	RTC_TimeStructure.RTC_Minutes = 0x55;
//	RTC_TimeStructure.RTC_Seconds = 0x00; 
//	
//	RTC_SetTime(RTC_Format_BCD, &RTC_TimeStructure);   

	/* Indicator for the RTC configuration���ݼĴ��� */
	//RTC_WriteBackupRegister(RTC_BKP_DR0, 0x32F2);
	
//	//�رջ��ѹ���
//	RTC_WakeUpCmd(DISABLE);

//	//Ϊ���ѹ���ѡ��RTC���úõ�ʱ��Դ
//	RTC_WakeUpClockConfig(RTC_WakeUpClock_CK_SPRE_16bits);

//	//���û��Ѽ���ֵΪ�Զ����أ�д��ֵĬ����0
//	RTC_SetWakeUpCounter(1-1);

	//���RTC�����жϱ�־
	RTC_ClearITPendingBit(RTC_IT_WUT);

	//ʹ��RTC�����ж�
	RTC_ITConfig(RTC_IT_WUT,ENABLE);

	//ʹ�ܻ��ѹ���
	RTC_WakeUpCmd(ENABLE);

/* RTC Alarm A Interrupt Configuration */
   /* EXTI configuration *******************************************************/
	EXTI_ClearITPendingBit(EXTI_Line22);
	EXTI_InitStructure.EXTI_Line = EXTI_Line22;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* Enable the RTC Alarm Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = RTC_WKUP_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}


void RTC_Print(void)
{

	
	RTC_DateTypeDef RTC_DateStructu;
	RTC_TimeTypeDef RTC_TimeStructure;
	
	
	//��ȡ����
	RTC_GetDate(RTC_Format_BCD,&RTC_DateStructu);
	
	printf("20%02x/%02x/%02x Week:%x\r\n",RTC_DateStructu.RTC_Year,
										 RTC_DateStructu.RTC_Month,
										 RTC_DateStructu.RTC_Date,
										 RTC_DateStructu.RTC_WeekDay);  
		
	//��ȡʱ��
	RTC_GetTime(RTC_Format_BCD,&RTC_TimeStructure);
	printf("%02x:%02x:%02x\r\n",RTC_TimeStructure.RTC_Hours,
                                RTC_TimeStructure.RTC_Minutes,
                                RTC_TimeStructure.RTC_Seconds);

	
}

//void Rtc_Alarm_Set(void)
//{
//	
//}

void RTC_WKUP_IRQHandler(void)
{
//	u8 d;
	//����־λ
	if(RTC_GetITStatus(RTC_IT_WUT) == SET)
	{
		
		//���ڴ�ӡ������һ�������豸��
		//printf("RTC_WKUP_IRQHandler\r\n");
		
		//g_rtc_wakeup_event=1;
		
		//��ձ�־λ
		RTC_ClearITPendingBit(RTC_IT_WUT);
		
		EXTI_ClearITPendingBit(EXTI_Line22);
		
	}
}







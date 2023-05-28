#include "sys.h"

static GPIO_InitTypeDef  GPIO_InitStructure;
static USART_InitTypeDef USART_InitStructure;
static NVIC_InitTypeDef NVIC_InitStructure;


void USART1_Init(u32 baud)
{
	
	//��PAӲ��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	//�򿪴���1Ӳ��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	
	//����PA9��PA10Ϊ���ù���ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//��PA9��PA10�������ӵ�����1��Ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	
	//���ô���1��ز����������ʡ���У��λ��8λ����λ��1��ֹͣλ......
	USART_InitStructure.USART_BaudRate = baud;						//���ò�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//8λ����λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			//1��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;			//����żУ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ��������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�����շ�����
	USART_Init(USART1,&USART_InitStructure);
	
	//���ô���1���жϴ�������������һ���ֽڴ����ж�
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	//���ô���1���ж����ȼ�
	/* Enable the USARTx Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//ʹ�ܴ���1����
	/* Enable USART */
	USART_Cmd(USART1, ENABLE);
	
}

void USART1_IRQHandler(void)
{
	u8 d;

	//����־λ
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
	{
//		//��������
		d = USART_ReceiveData(USART1);
		
		//�����յ������ݣ�������PC
//		USART_SendData(USART1, d);
//		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
		
		//����LED1
//		if(d == '1') PFout(9)=0;
//		if(d == 'A') PFout(9)=1;
//		if(d == 0x01) PFout(9)=0;
//		if(d == 0xf1) PFout(9)=1;
		
		//��ձ�־λ
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}

	
}


//�ض���
/***************************************????????***************************************************/

#if 1
struct __FILE {int handle; /*Add whatever you need here*/};
FILE __stdout;
FILE __stdin;
int fputc(int ch, FILE* f)
{
	USART_SendData(USART1,ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	return ch;
}
#endif


#if 0
struct __FILE {int handle; /*Add whatever you need here*/};
FILE __stdout;
FILE __stdin;
int fputc(int ch, FILE* f)
{
	USART_SendData(USART3,ch);
	while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET);
	return ch;
}
#endif





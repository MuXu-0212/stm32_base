#include "sys.h"

static GPIO_InitTypeDef GPIO_InitStruct;
static USART_InitTypeDef USART_InitStruct;
static NVIC_InitTypeDef NVIC_InitStruct;

void Usart1_Init(uint32_t baud)
{
	//1.ʹ��Ӳ��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	//ʹ�ܴ���ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	//2.��������
	GPIO_InitStruct.GPIO_Pin  	= GPIO_Pin_9 | GPIO_Pin_10;   	//��ʼ��PA9��10������
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AF;		//��������Ϊ����ģʽ
	GPIO_InitStruct.GPIO_Speed	= GPIO_High_Speed;  //����Ϊ������Ӧ 100Mhz
	GPIO_InitStruct.GPIO_OType  = GPIO_OType_PP;    //�������,�������
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_NOPULL; //����ģʽ �Ȳ�����Ҳ������
	GPIO_Init(GPIOA,&GPIO_InitStruct);

	//3.�Ѵ��ڵ�������PA9,10������
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9,  GPIO_AF_USART1); //����1������������
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1); //����1������������

	//4.���ô��ڽṹ��  ������  ��żУ��λ ����λ ֹͣλ
	USART_InitStruct.USART_BaudRate   =  baud; 							//Ӳ���Ĳ�����
	USART_InitStruct.USART_WordLength =  USART_WordLength_8b; 			//��Ч���ݵĳ���
	USART_InitStruct.USART_StopBits   =  USART_StopBits_1;    			//ֹͣλ Ϊ1
	USART_InitStruct.USART_Mode       =  USART_Mode_Rx | USART_Mode_Tx; //֧�������շ�
	USART_InitStruct.USART_Parity     =  USART_Parity_No; 				//����Ҫ��żУ��λ
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //����ҪӲ��������
	USART_Init(USART1, &USART_InitStruct);

	//5.ʹ�ܴ����ж�����
	USART_ITConfig(USART1, USART_IT_RXNE , ENABLE);
	
	NVIC_InitStruct.NVIC_IRQChannel					    = USART1_IRQn; //�����ж�ͨ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority	= 0x02;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority			= 0x02;
	NVIC_InitStruct.NVIC_IRQChannelCmd					= ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	//6.ʹ�ܴ��ڿ�ʼ����
	USART_Cmd(USART1, ENABLE);
}


void USART1_IRQHandler(void)
{
	uint8_t recv_data;
	//�жϱ�־λ���Ƿ�����ж�
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		recv_data = USART_ReceiveData(USART1);
		//while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
		
		//�ѽ��յ������ݽ���ת����PC��
		USART_SendData(USART1, recv_data);
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
		
		//������ݶ�ȡ��־λ
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}


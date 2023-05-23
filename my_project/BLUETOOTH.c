#include "sys.h"

static GPIO_InitTypeDef  GPIO_InitStructure;
static USART_InitTypeDef USART_InitStructure;
static NVIC_InitTypeDef NVIC_InitStructure;

void USART3_Init(u32 baud)
{
	
	//��PBӲ��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	//�򿪴���3Ӳ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	
	//����PB10��PB11Ϊ���ù���ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//��PB10��PB11�������ӵ�����3��Ӳ��
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3);
	
	//���ô���3��ز����������ʡ���У��λ��8λ����λ��1��ֹͣλ......
	USART_InitStructure.USART_BaudRate = baud;						//���ò�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//8λ����λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			//1��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;			//����żУ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ��������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�����շ�����
	USART_Init(USART3,&USART_InitStructure);
	
	//���ô���3���жϴ�������������һ���ֽڴ����ж�
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	
	//���ô���3���ж����ȼ�
	/* Enable the USARTx Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//ʹ�ܴ���3����
	/* Enable USART */
	USART_Cmd(USART3, ENABLE);
}

void USART3_Send_Str(char* str)
{
	char* p = str;
	while(*p!='\0')
	{
		USART_SendData(USART3, *p);
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET);	
		USART_ClearFlag(USART3,USART_FLAG_TXE);
		
		//ָ��ƫ��
		p++;
	}
	
}

//ATָ������ģ�飬����4.0ģ�鲻�ܸ��ֻ���������
void Ble_Config_Set(void)
{
	printf("This is ble test\r\n");
	//����AT�Ĳ���ָ��
	delay_ms(300);
	
	USART3_Send_Str("AT\r\n");
	delay_ms(300);
	
	//���͸���ģ������ָ��(��Ҫ��λ��Ч���������AT+RESET��������ģ������û�б��,��ô���¶�����ģ���ϵ�)
	USART3_Send_Str("AT+NAMECaster\r\n");
	delay_ms(300);
	
	//���͸�λģ���ָ��
	USART3_Send_Str("AT+RESET\r\n");
	delay_ms(2000);
	USART3_Send_Str("AT\r\n");
	delay_ms(300);
}



void USART3_IRQHandler(void)
{
	u8 d;

	//����־λ
	if(USART_GetITStatus(USART3,USART_IT_RXNE)==SET)
	{
		//��������
		d = USART_ReceiveData(USART3);
		
		printf("%c",d);
		
//		//ͨ������3���͸�PC
//		USART_ReceiveData(USART3);
//		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET);
		
		//��մ���3�Ķ�ȡ��־λ
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);
	}
}





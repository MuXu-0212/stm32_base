#include "sys.h"

static GPIO_InitTypeDef  GPIO_InitStructure;
static USART_InitTypeDef USART_InitStructure;
static NVIC_InitTypeDef NVIC_InitStructure;


void USART1_Init(u32 baud)
{
	
	//打开PA硬件时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	//打开串口1硬件时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	
	//配置PA9和PA10为复用功能模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//将PA9和PA10引脚链接到串口1的硬件
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	
	//配置串口1相关参数，波特率、无校验位、8位数据位、1歌停止位......
	USART_InitStructure.USART_BaudRate = baud;						//配置波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//8位数据位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			//1个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;			//无奇偶校验
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//允许收发数据
	USART_Init(USART1,&USART_InitStructure);
	
	//配置串口1的中断触发方法，接受一个字节触发中断
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	//配置串口1的中断优先级
	/* Enable the USARTx Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//使能串口1工作
	/* Enable USART */
	USART_Cmd(USART1, ENABLE);
	
}

void USART1_IRQHandler(void)
{
	u8 d;

	//检测标志位
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
	{
//		//接收数据
		d = USART_ReceiveData(USART1);
		
		//将接收到的数据，返发给PC
//		USART_SendData(USART1, d);
//		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
		
		//控制LED1
//		if(d == '1') PFout(9)=0;
//		if(d == 'A') PFout(9)=1;
//		if(d == 0x01) PFout(9)=0;
//		if(d == 0xf1) PFout(9)=1;
		
		//清空标志位
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}

	
}


//重定义
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





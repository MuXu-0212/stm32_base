#include "sys.h"

static GPIO_InitTypeDef GPIO_InitStruct;
static USART_InitTypeDef USART_InitStruct;
static NVIC_InitTypeDef NVIC_InitStruct;

void Usart1_Init(uint32_t baud)
{
	//1.使能硬件时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	//使能串口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	//2.配置引脚
	GPIO_InitStruct.GPIO_Pin  	= GPIO_Pin_9 | GPIO_Pin_10;   	//初始化PA9与10号引脚
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AF;		//配置引脚为复用模式
	GPIO_InitStruct.GPIO_Speed	= GPIO_High_Speed;  //配置为高速响应 100Mhz
	GPIO_InitStruct.GPIO_OType  = GPIO_OType_PP;    //推挽输出,增大电流
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_NOPULL; //浮空模式 既不上拉也不下拉
	GPIO_Init(GPIOA,&GPIO_InitStruct);

	//3.把串口的引脚与PA9,10相连接
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9,  GPIO_AF_USART1); //串口1发送数据引脚
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1); //串口1接收数据引脚

	//4.配置串口结构体  波特率  奇偶校验位 数据位 停止位
	USART_InitStruct.USART_BaudRate   =  baud; 							//硬件的波特率
	USART_InitStruct.USART_WordLength =  USART_WordLength_8b; 			//有效数据的长度
	USART_InitStruct.USART_StopBits   =  USART_StopBits_1;    			//停止位 为1
	USART_InitStruct.USART_Mode       =  USART_Mode_Rx | USART_Mode_Tx; //支持数据收发
	USART_InitStruct.USART_Parity     =  USART_Parity_No; 				//不需要奇偶校验位
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //不需要硬件控制流
	USART_Init(USART1, &USART_InitStruct);

	//5.使能串口中断配置
	USART_ITConfig(USART1, USART_IT_RXNE , ENABLE);
	
	NVIC_InitStruct.NVIC_IRQChannel					    = USART1_IRQn; //配置中断通道
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority	= 0x02;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority			= 0x02;
	NVIC_InitStruct.NVIC_IRQChannelCmd					= ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	//6.使能串口开始工作
	USART_Cmd(USART1, ENABLE);
}


void USART1_IRQHandler(void)
{
	uint8_t recv_data;
	//判断标志位，是否产生中断
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		recv_data = USART_ReceiveData(USART1);
		//while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
		
		//把接收到的数据进行转发给PC端
		USART_SendData(USART1, recv_data);
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
		
		//清空数据读取标志位
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}


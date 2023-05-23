#include "sys.h"

static GPIO_InitTypeDef  GPIO_InitStructure;
static USART_InitTypeDef USART_InitStructure;
static NVIC_InitTypeDef NVIC_InitStructure;

void USART3_Init(u32 baud)
{
	
	//打开PB硬件时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	//打开串口3硬件时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	
	//配置PB10和PB11为复用功能模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//将PB10和PB11引脚链接到串口3的硬件
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3);
	
	//配置串口3相关参数，波特率、无校验位、8位数据位、1个停止位......
	USART_InitStructure.USART_BaudRate = baud;						//配置波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//8位数据位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			//1个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;			//无奇偶校验
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//允许收发数据
	USART_Init(USART3,&USART_InitStructure);
	
	//配置串口3的中断触发方法，接受一个字节触发中断
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	
	//配置串口3的中断优先级
	/* Enable the USARTx Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//使能串口3工作
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
		
		//指针偏移
		p++;
	}
	
}

//AT指令配置模块，蓝牙4.0模块不能跟手机进行连接
void Ble_Config_Set(void)
{
	printf("This is ble test\r\n");
	//发送AT的测试指令
	delay_ms(300);
	
	USART3_Send_Str("AT\r\n");
	delay_ms(300);
	
	//发送更改模块名字指令(需要复位生效，如果发送AT+RESET搜索蓝牙模块名字没有变更,那么重新对蓝牙模块上电)
	USART3_Send_Str("AT+NAMECaster\r\n");
	delay_ms(300);
	
	//发送复位模块的指令
	USART3_Send_Str("AT+RESET\r\n");
	delay_ms(2000);
	USART3_Send_Str("AT\r\n");
	delay_ms(300);
}



void USART3_IRQHandler(void)
{
	u8 d;

	//检测标志位
	if(USART_GetITStatus(USART3,USART_IT_RXNE)==SET)
	{
		//接收数据
		d = USART_ReceiveData(USART3);
		
		printf("%c",d);
		
//		//通过串口3发送给PC
//		USART_ReceiveData(USART3);
//		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET);
		
		//清空串口3的读取标志位
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);
	}
}





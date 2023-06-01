#include "sys.h"

static SPI_InitTypeDef  SPI_InitStructure;
static GPIO_InitTypeDef GPIO_InitStructure;

void w25qxx_Init(void)
{
	//PB硬件时钟使能
	RCC_AHB1PeriphClockCmd(sFLASH_SPI_SCK_GPIO_CLK | sFLASH_SPI_MISO_GPIO_CLK | 
                          sFLASH_SPI_MOSI_GPIO_CLK | sFLASH_CS_GPIO_CLK, ENABLE);
	
	//SPI1硬件时钟使能
	sFLASH_SPI_CLK_INIT(sFLASH_SPI_CLK, ENABLE);
	
	//配置PB3~PB5为复用功能
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;

	
	//PB3~PB5连接到SPI1硬件

	
	//PB14配置输出模式
	
	//看时序图，PB14会有一个初始电平
	
	//配置SPI1的参数
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	//全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;			//主机模式
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//查看数据手册，8位数据
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;				//查看数据手册，SPI FLASH可以配置为高电平
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;			//查看数据手册，MISO引脚在时钟线第二边沿采样数据
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;				//片选引脚由代码控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;	//SPI1的硬件时钟源为APB2，SPI_CLK=84MHz/4=21
	
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(sFLASH_SPI, &SPI_InitStructure);
	
	//使能SPI1硬件工作
	SPI_Cmd(sFLASH_SPI, ENABLE);
}

u8 spi1_send_byte(u8 txd)
{
	//检查SPI1的发送缓冲区是否为空
	/*!< Loop while DR register in not emplty */
	while (SPI_I2S_GetFlagStatus(sFLASH_SPI, SPI_I2S_FLAG_TXE) == RESET);
	
	//通过SPI1硬件发送数据
	/*!< Send byte through the SPI1 peripheral */
	SPI_I2S_SendData(sFLASH_SPI, byte);
	
	//等待SPI1硬件发送数据
	/*!< Wait to receive a byte */
	while (SPI_I2S_GetFlagStatus(sFLASH_SPI, SPI_I2S_FLAG_RXNE) == RESET);
	
	//返回接收到的数据
	/*!< Return the byte read from the SPI bus */
	return SPI_I2S_ReceiveData(sFLASH_SPI);
	
}

u8 spi1_


void w25qxx_read_id(u8* m_id, u8* d_id)
{
	//片选引脚输出低电平
	PBout(14)=0;
	
	//发送90命令
	spi1_send_byte(0x90);
	
	//发送24bit地址，该数值全为0
	spi1_send_byte(0x00);
	spi1_send_byte(0x00);
	spi1_send_byte(0x00);
	
	//传递任意参数，读取厂商id
	*m_id = spi1_send_byte(0xFF);
	
	//传递任意参数，读取设备id
	*d_id = spi1_send_byte(0xFF);
	
	//片选引脚输出高电平，表示结束
	PBout(14)=0;
}





















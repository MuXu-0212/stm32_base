#include "sys.h"

static SPI_InitTypeDef  SPI_InitStructure;
static GPIO_InitTypeDef GPIO_InitStructure;

void w25qxx_Init(void)
{
	//PBӲ��ʱ��ʹ��
	RCC_AHB1PeriphClockCmd(sFLASH_SPI_SCK_GPIO_CLK | sFLASH_SPI_MISO_GPIO_CLK | 
                          sFLASH_SPI_MOSI_GPIO_CLK | sFLASH_CS_GPIO_CLK, ENABLE);
	
	//SPI1Ӳ��ʱ��ʹ��
	sFLASH_SPI_CLK_INIT(sFLASH_SPI_CLK, ENABLE);
	
	//����PB3~PB5Ϊ���ù���
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;

	
	//PB3~PB5���ӵ�SPI1Ӳ��

	
	//PB14�������ģʽ
	
	//��ʱ��ͼ��PB14����һ����ʼ��ƽ
	
	//����SPI1�Ĳ���
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	//ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;			//����ģʽ
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//�鿴�����ֲᣬ8λ����
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;				//�鿴�����ֲᣬSPI FLASH��������Ϊ�ߵ�ƽ
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;			//�鿴�����ֲᣬMISO������ʱ���ߵڶ����ز�������
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;				//Ƭѡ�����ɴ������
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;	//SPI1��Ӳ��ʱ��ԴΪAPB2��SPI_CLK=84MHz/4=21
	
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(sFLASH_SPI, &SPI_InitStructure);
	
	//ʹ��SPI1Ӳ������
	SPI_Cmd(sFLASH_SPI, ENABLE);
}

u8 spi1_send_byte(u8 txd)
{
	//���SPI1�ķ��ͻ������Ƿ�Ϊ��
	/*!< Loop while DR register in not emplty */
	while (SPI_I2S_GetFlagStatus(sFLASH_SPI, SPI_I2S_FLAG_TXE) == RESET);
	
	//ͨ��SPI1Ӳ����������
	/*!< Send byte through the SPI1 peripheral */
	SPI_I2S_SendData(sFLASH_SPI, byte);
	
	//�ȴ�SPI1Ӳ����������
	/*!< Wait to receive a byte */
	while (SPI_I2S_GetFlagStatus(sFLASH_SPI, SPI_I2S_FLAG_RXNE) == RESET);
	
	//���ؽ��յ�������
	/*!< Return the byte read from the SPI bus */
	return SPI_I2S_ReceiveData(sFLASH_SPI);
	
}

u8 spi1_


void w25qxx_read_id(u8* m_id, u8* d_id)
{
	//Ƭѡ��������͵�ƽ
	PBout(14)=0;
	
	//����90����
	spi1_send_byte(0x90);
	
	//����24bit��ַ������ֵȫΪ0
	spi1_send_byte(0x00);
	spi1_send_byte(0x00);
	spi1_send_byte(0x00);
	
	//���������������ȡ����id
	*m_id = spi1_send_byte(0xFF);
	
	//���������������ȡ�豸id
	*d_id = spi1_send_byte(0xFF);
	
	//Ƭѡ��������ߵ�ƽ����ʾ����
	PBout(14)=0;
}





















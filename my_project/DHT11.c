#include "sys.h"

static GPIO_InitTypeDef  GPIO_InitStructure;


void DHT11_Init(void)
{
	//��G�������ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	
	/* ����PG9λ���ģʽ */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	//PB6��ʼ��״̬λ�ߵ�ƽ����ʱ��ͼ
	PGout(9)=1;
}


//u32 DHT11_Read(u8* pbuf)
//{
//	
//	u32 t=0;
//	int32_t i=0, j=0;
//	u8 d=0;
//	u8* p=pbuf;
//	u32 check_sum=0;
//	
//	/* ����PG9λ���ģʽ */
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//	
//	GPIO_Init(GPIOG, &GPIO_InitStructure);
//	
//	PGout(9) = 1;
//	
//	PGout(9) = 0;
//	delay_ms(20);
//	PGout(9) = 1;
//	delay_us(30);

//	/* ����PG9λ����ģʽ */
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
//	GPIO_InitStructure.GPIO_OType= GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

//	
//	GPIO_Init(GPIOG, &GPIO_InitStructure);
//	
//	//�ȴ��͵�ƽ����
//	t=0;
//	while(PGin(9))
//	{
//		t++;
//		delay_us(1);
//		if (t>=4000)
//		{
//			return 1;
//		}
//	}
//	
//	//�����͵�ƽ�ĺϷ���
//	t=0;
//	while(PGin(9)==0)
//	{
//		t++;
//		delay_us(1);
//		if(t>=1000)
//		{
//			return 2;
//		}
//	}
//	
//	//�����ߵ�ƽ�ĺϷ���
//	t=0;
//	while(PGin(9))
//	{
//		t++;
//		delay_us(1);
//		if(t>=1000)
//		{
//			return 3;
//		}
//	}
//	
//	for(j=0; j<5; j++)
//	{
//		d=0;
//		//һ���ֽڵĽ���,�������Чλ��ʼ����
//		for(i=7;i>=0;i--)
//		{
//			//�ȴ�����0/����1��ǰ�õ͵�ƽ�������
//			t=0;
//			while(PGin(9)==0)
//			{
//				t++;
//				delay_us(1);
//				if(t>=1000)
//				{
//					return 4;
//				}
//			}
//			
//			//��ʱ40us
//			delay_us(40);
//			//�жϵ�ǰPG9�����Ƿ�Ϊ�ߵ�ƽ���ǵ͵�ƽ
//			//���Ǹߵ�ƽ����Ϊ����1
//			//���ǵ͵�ƽ����Ϊ����0
//			if(PGin(9))
//			{
//				d |= 1<<i;	//������d��Ӧ�ı���λ ��1,��i=7��d |=1<<7���ǽ�����d��bit7ֵ1
//				
//				//�ȴ��ߵ�ƽ�������
//				t=0;
//				while(PGin(9))
//				{
//					t++;
//					delay_us(1);
//					if(t>=1000)
//					{
//						return 5;
//					}
//				}
//			}
//		}
//		p[j]=d;
//	}
//	
//		
//	
//	//У���
//	check_sum = (p[0]+p[1]+p[2]+p[3])&0xFF;
//	if(p[4] != check_sum)
//	{
//		return 6;
//	}
//	
//	return 0;
//	
//}


void gpio_mode_out(void)
{
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
}

void gpio_mode_in(void)
{
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
}


//������
u8 DHT11_Read_Byte(void)
{
	u8 mask,data;
	data=0;
	for(mask=0x80;mask!=0;mask>>=1)
	{
		if(DHT11_Bit())
		{
			data |= mask;
		}
		else
		{
			data &=~mask;
		}
		return data;
	}
}

u32 DHT11_Read(u8* pbuf)
{
	u8 count=0;
	/* ����PG9λ���ģʽ */
	gpio_mode_out();
	PGout(9)=0;
	delay_us(20);
	PGout(9)=1;
	delay_us(30);
	
	gpio_mode_in();
	while(!PGout(9)&&count<100)
	{
		count++;
		delay_us(1);
	}
	if(count>=100)
	{
		return 1;
	}
	else
	{
		count=0;
	}
	
	while(PGout(9)&&count<100)
	{
		count++;
		delay_us(1);
	}
	
	if(count>=100)
	{
		return 1;
	}
	else
	{
		count=0;
	}
	
	for(BUFSIZ=0x80; mask!=0; mask>>=1)
	{
		if()
	}
}   

DHT11_read
	
	



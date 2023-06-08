#include "sys.h"

static GPIO_InitTypeDef  GPIO_InitStructure;


void DHT11_Init(void)
{
	//打开G组的引脚时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	
	/* 配置PG9位输出模式 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	//PB6初始化状态位高电平，看时序图
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
//	/* 配置PG9位输出模式 */
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

//	/* 配置PG9位输入模式 */
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
//	GPIO_InitStructure.GPIO_OType= GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

//	
//	GPIO_Init(GPIOG, &GPIO_InitStructure);
//	
//	//等待低电平出现
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
//	//测量低电平的合法性
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
//	//测量高电平的合法性
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
//		//一个字节的接收,从最高有效位开始接收
//		for(i=7;i>=0;i--)
//		{
//			//等待数据0/数据1的前置低电平持续完毕
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
//			//延时40us
//			delay_us(40);
//			//判断当前PG9引脚是否为高电平还是低电平
//			//若是高电平，则为数据1
//			//若是低电平，则为数据0
//			if(PGin(9))
//			{
//				d |= 1<<i;	//将变量d对应的比特位 置1,如i=7，d |=1<<7就是将变量d的bit7值1
//				
//				//等待高电平持续完毕
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
//	//校验和
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


//方法二
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
	/* 配置PG9位输出模式 */
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


	
	



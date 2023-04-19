#include "sys.h"

static GPIO_InitTypeDef GPIO_InitStruct;
uint32_t t;

uint32_t is_low(uint32_t time)
{
    t=0;
    while(PGin(9)==0)
    {
        t++;
        delay_us(1);
        if(t>=time)
        return 1;    
    }	
	return 0;
}


void DHT11_Init(void)
{
	//打开G组的引脚时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	

	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_OType= GPIO_OType_PP;
	GPIO_Init(GPIOG, &GPIO_InitStruct);
	
	//把DHT11模块设置为高电平作为空闲状态
	PGout(9) = 1;
}

void DHT11_In_Mode(void)
{
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_OType= GPIO_OType_PP;
	GPIO_Init(GPIOG, &GPIO_InitStruct);
}

void DHT11_Out_Mode(void)
{
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_OType= GPIO_OType_PP;
	GPIO_Init(GPIOG, &GPIO_InitStruct);
	PGout(9) = 1;
}

int32_t DHT11_Read_Data(uint8_t *pbuf)
{
    int32_t i=0,j=0;
    uint8_t d=0;
    uint8_t *p=pbuf;
    uint32_t check_sum=0;
    
    //PG9号引脚为输出模式
    DHT11_Out_Mode();
 
    PGout(9)=0;
    delay_ms(20);
    PGout(9)=1;
    delay_us(30);    
    
    //PG9号引脚为输入模式
    DHT11_In_Mode();

    //等待低电平出现
    is_low(4000);
    
    //测量低电平合法性
    is_low(1000);
 
    //测量高电平合法性
    is_low(1000);
    
    for(j=0; j<5; j++)
    {
        d=0;
        //一个字节的接收，从最高有效位开始接收
        for(i=7; i>=0; i--)
        {
            //等待数据0/数据1的前置低电平持续完毕
            is_low(1000);

            //延时40us
            delay_us(40);
        
            //判断当前PG9是否为高电平还是低电平
            //若是高电平，则为数据1；
            //若是低电平，则为数据0；
            if(PGin(9))
            {
                d|=1<<i;//将变量d对应的比特位置1，如i=7，d|=1<<7就是将变量d的bit7置1
            
                //等待高电平持续完毕
                is_low(1000);     
            }
        }        
        p[j]=d;    
    }
    
    //校验和
    check_sum = (p[0]+p[1]+p[2]+p[3])&0xFF;    
    if(p[4] != check_sum)
    {
        return 6;
    }

	
	DHT11_Out_Mode();
    return 0;
}

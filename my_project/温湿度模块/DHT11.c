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
	//��G�������ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	

	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_OType= GPIO_OType_PP;
	GPIO_Init(GPIOG, &GPIO_InitStruct);
	
	//��DHT11ģ������Ϊ�ߵ�ƽ��Ϊ����״̬
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
    
    //PG9������Ϊ���ģʽ
    DHT11_Out_Mode();
 
    PGout(9)=0;
    delay_ms(20);
    PGout(9)=1;
    delay_us(30);    
    
    //PG9������Ϊ����ģʽ
    DHT11_In_Mode();

    //�ȴ��͵�ƽ����
    is_low(4000);
    
    //�����͵�ƽ�Ϸ���
    is_low(1000);
 
    //�����ߵ�ƽ�Ϸ���
    is_low(1000);
    
    for(j=0; j<5; j++)
    {
        d=0;
        //һ���ֽڵĽ��գ��������Чλ��ʼ����
        for(i=7; i>=0; i--)
        {
            //�ȴ�����0/����1��ǰ�õ͵�ƽ�������
            is_low(1000);

            //��ʱ40us
            delay_us(40);
        
            //�жϵ�ǰPG9�Ƿ�Ϊ�ߵ�ƽ���ǵ͵�ƽ
            //���Ǹߵ�ƽ����Ϊ����1��
            //���ǵ͵�ƽ����Ϊ����0��
            if(PGin(9))
            {
                d|=1<<i;//������d��Ӧ�ı���λ��1����i=7��d|=1<<7���ǽ�����d��bit7��1
            
                //�ȴ��ߵ�ƽ�������
                is_low(1000);     
            }
        }        
        p[j]=d;    
    }
    
    //У���
    check_sum = (p[0]+p[1]+p[2]+p[3])&0xFF;    
    if(p[4] != check_sum)
    {
        return 6;
    }

	
	DHT11_Out_Mode();
    return 0;
}

#ifndef __SYS_H_
#define __SYS_H_

#include "stm32f4xx.h"
#include <stdio.h>

#define uint32_t u32
#define uint16_t u16
#define uint8_t  u8



//重定义
/***************************************????????***************************************************/
//struct __FILE {int handle; /*Add whatever you need here*/};
//FILE __stdout;
//FILE __stdin;
//int fputc(int ch, FILE* f)
//{
//	USART_SendData(USART1,ch);
//	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
//	return ch;
//}

/***************************************????????***************************************************/

//位带操作，实现51类似的GPIO控制功能
/***************************************????????***************************************************/
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

#define GPIOA_ODR_Addr    (GPIOA_BASE+20) //0x40020014
#define GPIOB_ODR_Addr    (GPIOB_BASE+20) //0x40020414 
#define GPIOC_ODR_Addr    (GPIOC_BASE+20) //0x40020814 
#define GPIOD_ODR_Addr    (GPIOD_BASE+20) //0x40020C14 
#define GPIOE_ODR_Addr    (GPIOE_BASE+20) //0x40021014 
#define GPIOF_ODR_Addr    (GPIOF_BASE+20) //0x40021414    
#define GPIOG_ODR_Addr    (GPIOG_BASE+20) //0x40021814   
#define GPIOH_ODR_Addr    (GPIOH_BASE+20) //0x40021C14    
#define GPIOI_ODR_Addr    (GPIOI_BASE+20) //0x40022014     

#define GPIOA_IDR_Addr    (GPIOA_BASE+16) //0x40020010 
#define GPIOB_IDR_Addr    (GPIOB_BASE+16) //0x40020410 
#define GPIOC_IDR_Addr    (GPIOC_BASE+16) //0x40020810 
#define GPIOD_IDR_Addr    (GPIOD_BASE+16) //0x40020C10 
#define GPIOE_IDR_Addr    (GPIOE_BASE+16) //0x40021010 
#define GPIOF_IDR_Addr    (GPIOF_BASE+16) //0x40021410 
#define GPIOG_IDR_Addr    (GPIOG_BASE+16) //0x40021810 
#define GPIOH_IDR_Addr    (GPIOH_BASE+16) //0x40021C10 
#define GPIOI_IDR_Addr    (GPIOI_BASE+16) //0x40022010 
 
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  // 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  // 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  // 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  // 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  // 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  // 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  // 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  // 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  // 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  // 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  // 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //

#define PHout(n)   BIT_ADDR(GPIOH_ODR_Addr,n)  // 
#define PHin(n)    BIT_ADDR(GPIOH_IDR_Addr,n)  //

#define PIout(n)   BIT_ADDR(GPIOI_ODR_Addr,n)  // 
#define PIin(n)    BIT_ADDR(GPIOI_IDR_Addr,n)  //


/***************************************************************************************/
//在头文件里声明函数
extern void LED_Init(void);
extern void delay_led(void);

extern void KEY_Init(void);
extern void delay_key(void);

extern void EXTILine0_Init(void);
extern void EXTI0_IRQHandler(void);
extern void SYS_TIMER(void);
extern uint32_t delay_ms(uint32_t n);
extern uint32_t delay_us(uint32_t n);
extern void TIM3_INIT(void);

extern void TIM14_Init(void);
extern void TIM1_Init(void);

extern void USART1_Init(u32 baud);
extern void DHT11_Init(void);


extern void USART3_Init(u32 baud);	//蓝牙模块
extern void USART3_Send_Str(char* str);
extern void Ble_Config_Set(void); ////发送AT的测试指令

extern void DHT11_Init(void);
extern u32 DHT11_Read(u8* pbuf);

//extern void DHT11_In_Mode(void);
//extern void DHT11_Out_Mode(void);
//extern int32_t DHT11_Read_Data(uint8_t *pbuf);

extern void rtc_init(void);
extern void RTC_Print(void);
extern void rtc_reinit(void);

extern void IWDG_Init(void);
extern void WWDG_Init(void);

extern void adc_init(void);

extern void w25qxx_Init(void);
extern u8 spi1_send_byte(u8 txd);
extern void w25qxx_read_id(u8* m_id, u8* d_id);
#endif

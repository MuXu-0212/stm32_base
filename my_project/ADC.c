#include "sys.h"

static ADC_InitTypeDef       ADC_InitStructure;
static ADC_CommonInitTypeDef ADC_CommonInitStructure;
//static DMA_InitTypeDef       DMA_InitStructure;
static GPIO_InitTypeDef      GPIO_InitStructure;

void adc_init(void)
{
	//打开ADC的硬件时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	//打开PA的硬件时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	//配置PA5引脚为模拟信号引脚
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;		//模拟信号
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	//GPIOAF专门用于数字硬件
	
	
	/* ADC Common Init **********************************************************/
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;						//独立工作模式，只使用一个ADC		
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;                     //ADC硬件时钟=84MHz/2=42MHz,Tadc=1/42MHz
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;         //不需要映射数据，直接读取寄存器就可以得到结果值
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;    //5*Tadc
	ADC_CommonInit(&ADC_CommonInitStructure);
	
	/* ADC1 Init ****************************************************************/
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;							//12位精度
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;                                   //单个通道，否则为多个通道
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;                              //不断的进行转换
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;     //不需要内部脉冲触发adc工作
	//ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;           
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;                          //右对齐存储
	ADC_InitStructure.ADC_NbrOfConversion = 1;                                      //只有单个通道
	ADC_Init(ADC1, &ADC_InitStructure);

	/* ADC1 regular channe5 configuration **************************************/
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_3Cycles);
	
	/* Enable DMA request after last transfer (Single-ADC mode) */
	//ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
	
	/* Enable ADC1 DMA */
	//ADC_DMACmd(ADC1, ENABLE);
	
	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);

}


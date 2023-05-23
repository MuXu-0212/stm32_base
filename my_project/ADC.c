#include "sys.h"

static ADC_InitTypeDef       ADC_InitStructure;
static ADC_CommonInitTypeDef ADC_CommonInitStructure;
//static DMA_InitTypeDef       DMA_InitStructure;
static GPIO_InitTypeDef      GPIO_InitStructure;

void adc_init(void)
{
	//��ADC��Ӳ��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	//��PA��Ӳ��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	//����PA5����Ϊģ���ź�����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;		//ģ���ź�
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	//GPIOAFר����������Ӳ��
	
	
	/* ADC Common Init **********************************************************/
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;						//��������ģʽ��ֻʹ��һ��ADC		
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;                     //ADCӲ��ʱ��=84MHz/2=42MHz,Tadc=1/42MHz
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;         //����Ҫӳ�����ݣ�ֱ�Ӷ�ȡ�Ĵ����Ϳ��Եõ����ֵ
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;    //5*Tadc
	ADC_CommonInit(&ADC_CommonInitStructure);
	
	/* ADC1 Init ****************************************************************/
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;							//12λ����
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;                                   //����ͨ��������Ϊ���ͨ��
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;                              //���ϵĽ���ת��
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;     //����Ҫ�ڲ����崥��adc����
	//ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;           
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;                          //�Ҷ���洢
	ADC_InitStructure.ADC_NbrOfConversion = 1;                                      //ֻ�е���ͨ��
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


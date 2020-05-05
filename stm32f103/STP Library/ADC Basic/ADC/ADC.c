#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_adc.h"

void ADC1_Init(){
	
	    ADC_InitTypeDef ADC_InitStruct;

	    GPIO_InitTypeDef GPIO_InitStruct;

	    // Step 1: Initialize ADC1
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
   		ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
	    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
      ADC_InitStruct.ADC_ExternalTrigConv = DISABLE;
	    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	    ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
	    ADC_InitStruct.ADC_NbrOfChannel = 1;
	    ADC_InitStruct.ADC_ScanConvMode = DISABLE;
	    ADC_Init(ADC1, &ADC_InitStruct);
	    ADC_Cmd(ADC1, ENABLE);

	    // ADC1 channel 1 (PA1)

      ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1,ADC_SampleTime_7Cycles5);
		

	    // Step 2: Initialize GPIOA (PA1) for analog input

	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	    GPIO_Init(GPIOA, &GPIO_InitStruct);
		}
	
uint16_t ADC1_READ(void)
{
		ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	
		while (!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
		return ADC_GetConversionValue(ADC1);
		}
		
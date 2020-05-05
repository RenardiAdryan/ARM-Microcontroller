#include "stm32f10x.h"
#include "stm32f10x_GPIO.h"
#include "stdio.h"
#define BUF_SIZE	50

GPIO_InitTypeDef 				GPIO_InitStructure;
NVIC_InitTypeDef        NVIC_InitStruct;
ADC_InitTypeDef         ADC_InitStruct;
USART_InitTypeDef       USART_InitStruct;

uint32_t ADC_value[2];

volatile uint32_t adcval[4];
volatile uint8_t ch=0;

  uint32_t ADC_value[2];
 char xstring[BUF_SIZE];

void USART_PutChar(USART_TypeDef*USARTx,uint8_t x)
{	
	USARTx->DR=x;
	while(!(USARTx->SR & USART_FLAG_TXE));
	USARTx->SR &=~ USART_FLAG_TXE;
}


void USART_Puts(USART_TypeDef*USARTx,char *s)
{
	// Send a string
	while (*s)
	{
		USART_PutChar(USARTx,*s++);
	}
}





void ADC1_2_IRQHandler(){
	
adcval[ch]=ADC_GetConversionValue(ADC1);
ADC_ClearITPendingBit(ADC1,ADC_IT_EOC);
ADC_SoftwareStartConvCmd(ADC1,ENABLE);
ch++;
if(ch==2){ch=0;}
}
void ADCInit(){
 //configure ADC1 parameters
	RCC_ADCCLKConfig(RCC_PCLK2_Div6); //clock for ADC (max 14MHz, 72/6=12MHz)
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //enable ADC clock

  ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStruct.ADC_ScanConvMode = ENABLE;
  ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStruct.ADC_NbrOfChannel  = 1;
  ADC_Init(ADC1, &ADC_InitStruct);
  
  ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_55Cycles5); //PC2 as Input
  //ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 2, ADC_SampleTime_55Cycles5); //PC1 as Input
	
	//ADC_DMACmd(ADC1, ENABLE);
  ADC_ITConfig(ADC1,ADC_IT_EOC,ENABLE);
	ADC_Cmd(ADC1,ENABLE);
  
	 //Calibrate ADC *optional?
  ADC_ResetCalibration(ADC1);
  while(ADC_GetResetCalibrationStatus(ADC1));
  ADC_StartCalibration(ADC1);
  while(ADC_GetCalibrationStatus(ADC1));

	 ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	 
	 
	 NVIC_EnableIRQ(ADC1_2_IRQn);
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
		NVIC_InitStruct.NVIC_IRQChannel =ADC1_2_IRQn;
	  NVIC_InitStruct.NVIC_IRQChannelSubPriority=0x04;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 4;
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStruct);


}

void USART3Init(){
			
	//INitialize USART 2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits =USART_StopBits_1;;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART3,&USART_InitStruct);
	USART_Cmd(USART3,ENABLE);
	
}

int main(){
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin		=	GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode	=	GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Speed	=	GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//==========LED===============
	GPIO_InitStructure.GPIO_Pin		=	GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode	=	GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed	=	GPIO_Speed_10MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	//initialize tx
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	//initialize rx
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
  
	ADCInit();
	USART3Init();
while(1){
sprintf(xstring,"ADC A5 = %d || ADC A4 = %d  \n",adcval[0],adcval[1]);
	USART_Puts(USART3,xstring);
}

}
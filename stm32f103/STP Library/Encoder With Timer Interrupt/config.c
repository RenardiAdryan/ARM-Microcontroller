#include "stm32f10x_gpio.h"
#include "stm32f10x_RCC.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_USART.h"

GPIO_InitTypeDef 				GPIO_InitStructu;
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
NVIC_InitTypeDef NVIC_InitStruct;
USART_InitTypeDef USART_InitStruct;

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


void USARTInterruptInit(){
		USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
		NVIC_EnableIRQ(USART3_IRQn);
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
		NVIC_SetPriority(SysTick_IRQn,0);
		NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStruct);

}

void rotaryInit(){
	
	    // Step 2: Setup TIM4 for encoder input

	    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	    TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12,
	    TIM_ICPolarity_Rising, TIM_ICPolarity_Falling);
	    TIM_Cmd(TIM4, ENABLE);
	
	
	    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	    TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12,
	    TIM_ICPolarity_Rising, TIM_ICPolarity_Falling);
	    TIM_Cmd(TIM3, ENABLE);
}

void GPIOInit(){


	    // Step 1: Initialize GPIO as input for rotary encoder

	    // PB7 (TIM4_CH2) (encoder pin A), PB6 (TIM4_CH1) (encoder pin B)

	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE);
	    GPIO_InitStructu.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6;
	    GPIO_InitStructu.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	    GPIO_InitStructu.GPIO_Speed = GPIO_Speed_2MHz;
	    GPIO_Init(GPIOB, &GPIO_InitStructu);
	
	
	
	    
			// PA7 (TIM3_CH2) (encoder pin A), PA6 (TIM3_CH1) (encoder pin B)

	    GPIO_InitStructu.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6;
	    GPIO_InitStructu.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	    GPIO_InitStructu.GPIO_Speed = GPIO_Speed_2MHz;
	    GPIO_Init(GPIOA, &GPIO_InitStructu);
	
	//initialize tx
	GPIO_InitStructu.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructu.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructu.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructu);

	//initialize rx
	GPIO_InitStructu.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructu.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructu.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructu);


		GPIO_InitStructu.GPIO_Pin = GPIO_Pin_3;
		GPIO_InitStructu.GPIO_Mode =GPIO_Mode_Out_PP;
		GPIO_InitStructu.GPIO_Speed= GPIO_Speed_2MHz;
		GPIO_Init(GPIOA,&GPIO_InitStructu);

}


void USART3_PutChar(char c)
{
	// Wait until transmit data register is empty
	while (!USART_GetFlagStatus(USART3, USART_FLAG_TXE));
	// Send a char using USART3
	USART_SendData(USART3, c);
}

void USART3_PutString(char *s)
{
	// Send a string
	while (*s)
	{
		USART3_PutChar(*s++);
	}
}
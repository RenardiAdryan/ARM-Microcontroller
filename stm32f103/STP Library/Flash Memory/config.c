#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
#include "uc_memory.h"
//INitialize struct
   USART_InitTypeDef USART_InitStruct;
	 GPIO_InitTypeDef GPIO_InitStructure;
	 NVIC_InitTypeDef NVIC_InitStruct;

void USART3Init(){
			
	//INitialize USART 3
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits =USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;//8 bit data
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


void GPIOInit(){

RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);
	//initialize tx USART 3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	//initialize rx USART 3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	

	
	
	//initialize pin active lcd
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIOA->BSRR = (1<<3);
	
  //initialize pin rotary encoder
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7|GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure); 
	
	
	
	  //initialize pin BUTTON 1 and BUTTON 2

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
		
	
}

void Kirim1Byte(USART_TypeDef*USARTx, unsigned char x){
//kirim data  karakter
	USARTx->DR=x;
	while(!(USARTx->SR & USART_FLAG_TXE));
	USARTx->SR &=~ USART_FLAG_TXE;
}


void USART3_PutChar(unsigned char c)
{
	// Wait until transmit data register is empty
	while (!USART_GetFlagStatus(USART3, USART_FLAG_TXE));
	// Send a char using USART3
	USART_SendData(USART3, c);
}

void USART3_PutString(unsigned char *s)
{
	// Send a string
	while (*s)
	{
		USART3_PutChar(*s++);
	}
	
}


void EEPROM_PutString(uint16_t Address,unsigned char *s)
{
	// Send a string
	while (*s)
	{
	  FEE_WriteDataByte (Address,*s++);
	}
	
}

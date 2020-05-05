#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include "misc.h"

GPIO_InitTypeDef GPIO_Initstructure;
NVIC_InitTypeDef NVIC_InitStructure;
USART_InitTypeDef USART_InitStructure;

void GPIOInit(){
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
GPIO_Initstructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
GPIO_Initstructure.GPIO_OType=GPIO_OType_PP;
GPIO_Initstructure.GPIO_PuPd =GPIO_PuPd_UP;
GPIO_Initstructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
GPIO_Init(GPIOD,&GPIO_Initstructure);
	
		
//===================USART======GPIO=============	
GPIO_Initstructure.GPIO_Mode=GPIO_Mode_AF;
GPIO_Initstructure.GPIO_Speed=GPIO_Speed_2MHz;
GPIO_Initstructure.GPIO_OType=GPIO_OType_PP;
GPIO_Initstructure.GPIO_PuPd = GPIO_PuPd_UP;
GPIO_Initstructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_10|GPIO_Pin_11;
GPIO_Init(GPIOC,&GPIO_Initstructure);
	
/*	
GPIO_Initstructure.GPIO_Mode=GPIO_Mode_AF;
GPIO_Initstructure.GPIO_Speed=GPIO_Speed_2MHz;
GPIO_Initstructure.GPIO_OType=GPIO_OType_PP;
GPIO_Initstructure.GPIO_PuPd = GPIO_PuPd_UP;
GPIO_Initstructure.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_9;
GPIO_Init(GPIOA,&GPIO_Initstructure);
*/

GPIO_Initstructure.GPIO_Mode=GPIO_Mode_AF;
GPIO_Initstructure.GPIO_Speed=GPIO_Speed_2MHz;
GPIO_Initstructure.GPIO_OType=GPIO_OType_PP;
GPIO_Initstructure.GPIO_PuPd = GPIO_PuPd_UP;
GPIO_Initstructure.GPIO_Pin=GPIO_Pin_7|GPIO_Pin_6;
GPIO_Init(GPIOB,&GPIO_Initstructure);

}

void InteruptInit(){
USART_ITConfig(USART6,USART_IT_RXNE,ENABLE);	
NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //prioritas e seng ndi seng utama
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);
	
	
USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //prioritas e seng ndi seng utama
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);


}


void USARTInit(){
RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);

GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);
GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);

USART_OverSampling8Cmd(USART6,DISABLE);
USART_InitStructure.USART_BaudRate 		= 9600;
USART_InitStructure.USART_WordLength	= USART_WordLength_8b;
USART_InitStructure.USART_StopBits		= USART_StopBits_1;
USART_InitStructure.USART_Parity			= USART_Parity_No;
USART_InitStructure.USART_Mode 				= USART_Mode_Rx | USART_Mode_Tx;
USART_InitStructure.USART_HardwareFlowControl	= USART_HardwareFlowControl_None;
USART_Init(USART6,&USART_InitStructure);	
USART_ITConfig(USART6,USART_IT_RXNE,ENABLE);
USART_Cmd(USART6,ENABLE);

	
	
RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);
GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);

USART_OverSampling8Cmd(USART3,DISABLE);
USART_InitStructure.USART_BaudRate 		= 9600;
USART_InitStructure.USART_WordLength	= USART_WordLength_8b;
USART_InitStructure.USART_StopBits		= USART_StopBits_1;
USART_InitStructure.USART_Parity			= USART_Parity_No;
USART_InitStructure.USART_Mode 				= USART_Mode_Rx | USART_Mode_Tx;
USART_InitStructure.USART_HardwareFlowControl	= USART_HardwareFlowControl_None;
USART_Init(USART3,&USART_InitStructure);	
USART_Cmd(USART3,ENABLE);


RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
//GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
//GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);

GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);
GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);

USART_OverSampling8Cmd(USART1,DISABLE);
USART_InitStructure.USART_BaudRate 		= 115200;
USART_InitStructure.USART_WordLength	= USART_WordLength_8b;
USART_InitStructure.USART_StopBits		= USART_StopBits_1;
USART_InitStructure.USART_Parity			= USART_Parity_No;
USART_InitStructure.USART_Mode 				= USART_Mode_Rx | USART_Mode_Tx;
USART_InitStructure.USART_HardwareFlowControl	= USART_HardwareFlowControl_None;
USART_Init(USART1,&USART_InitStructure);	
USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
USART_Cmd(USART1,ENABLE);






}


void USART1_ftdi_Active(){

}


void USART1_IMU_Active(){




}


void USART6_PutChar(uint8_t c)
{
	// Wait until transmit data register is empty
	while (!USART_GetFlagStatus(USART6, USART_FLAG_TXE));
	// Send a char using USART3
	USART_SendData(USART6, c);
}

void USART6_Puts(char *s)
{
	// Send a string
	while (*s)
	{
		USART6_PutChar(*s++);
	}
}

uint8_t USART6_getchar(void){

	char c;
	while (!USART_GetFlagStatus(USART6, USART_FLAG_RXNE));
	c=USART_ReceiveData(USART6);
  return c;
}





void USART3_PutChar(uint8_t x)
{	
	USART3->DR = x;
	while(!(USART3->SR & USART_FLAG_TXE)){}
  USART3->SR &= ~USART_FLAG_TXE; 
}

void USART3_Puts(char *s)
{
	// Send a string
	while (*s)
	{
		USART3_PutChar(*s++);
	}
}

uint8_t USART3_getchar(void){

	char c;
	while (!USART_GetFlagStatus(USART3, USART_FLAG_RXNE));
	c=USART_ReceiveData(USART3);
  return c;
}



void USART1_PutChar(uint8_t x)
{	
	USART1->DR = x;
	while(!(USART1->SR & USART_FLAG_TXE)){}
  USART1->SR &= ~USART_FLAG_TXE; 
}

void USART1_Puts(char *s)
{
	// Send a string
	while (*s)
	{
		USART1_PutChar(*s++);
	}
}

uint8_t USART1_getchar(void){

	char c;
	while (!USART_GetFlagStatus(USART1, USART_FLAG_RXNE));
	c=USART_ReceiveData(USART1);
  return c;
}
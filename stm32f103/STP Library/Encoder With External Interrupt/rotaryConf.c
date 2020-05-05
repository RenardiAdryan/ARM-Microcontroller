#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "misc.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_rcc.h"
GPIO_InitTypeDef GPIO_InitStructure;
EXTI_InitTypeDef EXTI_InitStruct;
NVIC_InitTypeDef NVIC_InitStruct;
void rotaryInit(){
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource6);
	    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource7);
	    EXTI_InitStruct.EXTI_Line = EXTI_Line6 | EXTI_Line7;
	    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	    EXTI_Init(&EXTI_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;
	    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
	    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
	    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	    NVIC_Init(&NVIC_InitStruct);
}

void GPIOInit(){

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7|GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure); 
	
}
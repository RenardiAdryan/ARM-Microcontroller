#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_SYSCFG.h"
#include "misc.h"

GPIO_InitTypeDef GPIO_Initstructure;
NVIC_InitTypeDef NVIC_InitStructure;
EXTI_InitTypeDef EXTI_InitStruct;


void GPIOInit(){
	
		
//=========================BUTTON===========================
	
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
GPIO_Initstructure.GPIO_Mode=GPIO_Mode_IN;
GPIO_Initstructure.GPIO_Speed=GPIO_Speed_2MHz;
GPIO_Initstructure.GPIO_OType=GPIO_OType_PP;
GPIO_Initstructure.GPIO_PuPd = GPIO_PuPd_UP;
GPIO_Initstructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3
														|GPIO_Pin_4|GPIO_Pin_5;
GPIO_Init(GPIOE,&GPIO_Initstructure);

 //====BUtton interupt pin E6====
    GPIO_Initstructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_Initstructure.GPIO_OType = GPIO_OType_PP;
    GPIO_Initstructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_Initstructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Initstructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOE,&GPIO_Initstructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
GPIO_Initstructure.GPIO_Mode=GPIO_Mode_OUT;
GPIO_Initstructure.GPIO_Speed=GPIO_Speed_2MHz;
GPIO_Initstructure.GPIO_OType=GPIO_OType_PP;
GPIO_Initstructure.GPIO_PuPd = GPIO_PuPd_UP;
GPIO_Initstructure.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
GPIO_Init(GPIOD,&GPIO_Initstructure);

}
void InterruptInit(){
//==============EXTI_6===========>MENU===============
NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
    /* Set priority */
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
    /* Set sub priority */
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
    /* Enable interrupt */
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    /* Add to NVIC */
    NVIC_Init(&NVIC_InitStructure);
	

}



void EXTI_ButtonConfig(){
RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
 /* Tell system that you will use PB12 for EXTI_Line12 */
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource6);
    
    /* PE6 is connected to EXTI_Line6 */
    EXTI_InitStruct.EXTI_Line = EXTI_Line6;
    /* Enable interrupt */
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    /* Interrupt mode */
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    /* Triggers on rising and falling edge */
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    /* Add to EXTI */
    EXTI_Init(&EXTI_InitStruct);	
}


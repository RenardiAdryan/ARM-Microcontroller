#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"



GPIO_InitTypeDef GPIO_Initstructure;

void GPIOInit(){

RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
//=========================LAMPUUU==========================	

GPIO_Initstructure.GPIO_Mode=GPIO_Mode_OUT;
GPIO_Initstructure.GPIO_Speed=GPIO_Speed_2MHz;
GPIO_Initstructure.GPIO_OType=GPIO_OType_PP;
GPIO_Initstructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Initstructure.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_12|GPIO_Pin_14|GPIO_Pin_15;
GPIO_Init(GPIOD,&GPIO_Initstructure);

//=========================BUTTON===========================
GPIO_Initstructure.GPIO_Mode=GPIO_Mode_IN;
GPIO_Initstructure.GPIO_Speed=GPIO_Speed_2MHz;
GPIO_Initstructure.GPIO_OType=GPIO_OType_PP;
GPIO_Initstructure.GPIO_PuPd = GPIO_PuPd_DOWN;
GPIO_Initstructure.GPIO_Pin=GPIO_Pin_0;
GPIO_Init(GPIOA,&GPIO_Initstructure);

}


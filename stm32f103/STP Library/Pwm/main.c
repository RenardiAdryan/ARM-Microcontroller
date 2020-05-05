#include "stm32f10x.h"
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h" 
void delay(unsigned int nCount);
GPIO_InitTypeDef 				GPIO_InitStructure;
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
TIM_OCInitTypeDef  			TIM_OCInitStructure;
TIM_ICInitTypeDef 			TIM_ICInitStruct;
uint16_t i;
int main(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3|GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure); 
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	
	TIM_TimeBaseStructure.TIM_Period = 2000-1;													//set nilai autoreload Timer 3
	TIM_TimeBaseStructure.TIM_Prescaler = 18-1 ; //1000 hz							//set nilai presscaller
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;												//clockdivision, diisi 0 ae
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;					//counter mode counter up
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;										//mode PWM1,
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);										//tim8 OC4 PRELOAD ENABLE
	
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);										//tim4 OC2 PRELOAD ENABLE	
	
	TIM_ARRPreloadConfig(TIM2, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
	
	
	while(1){
	
		for(i=0;i<=2000;i++){
		TIM2->CCR3=i;
	  TIM2->CCR4=i;
		delay(10);
		}
		
		delay(1000);
		
	}
}

void delay(unsigned int nCount)
	{
	    unsigned int i, j;
	    for (i = 0; i < nCount; i++)
	        for (j = 0; j < 0x2AFF; j++);
	}
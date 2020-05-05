#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "misc.h"
GPIO_InitTypeDef 				GPIO_InitStructure;
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
TIM_OCInitTypeDef  			TIM_OCInitStructure;
TIM_ICInitTypeDef 			TIM_ICInitStruct;

void TIM2_INT_Init(void);
	NVIC_InitTypeDef NVIC_InitStruct;
void TIM2Init(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	//prescaller-1=(clockAPB/T period)*freq
	//ps-1 = 36000000/2000*1000hz = 18;
	TIM_TimeBaseStructure.TIM_Period = 2000-1;													//set nilai autoreload Timer 3
	TIM_TimeBaseStructure.TIM_Prescaler = 36000-1 ; //0.5 hz							//set nilai presscaller
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;												//clockdivision, diisi 0 ae
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;					//counter mode counter up
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;										//mode PWM1,
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
//	
//	TIM_OCInitStructure.TIM_Pulse = 0;
//	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
//	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);										//tim8 OC4 PRELOAD ENABLE
//	
//	TIM_OCInitStructure.TIM_Pulse = 0;
//	TIM_OC4Init(TIM2, &TIM_OCInitStructure);
//	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);										//tim4 OC2 PRELOAD ENABLE	
//	
//	TIM_ARRPreloadConfig(TIM2, ENABLE);
//	TIM_Cmd(TIM2, ENABLE);
	
	//enable TIM2 Interrupt
	TIM_ITConfig(TIM2,TIM_IT_Update, ENABLE);
	
	//start TIM2
	TIM_Cmd(TIM2,ENABLE);
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
}

//void TIM3Init(){
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
//	//ps-1 = 36000000/2000*1000hz=18;
//	TIM_TimeBaseStructure.TIM_Period = 2000-1;													//set nilai autoreload Timer 3
//	TIM_TimeBaseStructure.TIM_Prescaler = 18000-1 ; //1000 hz							//set nilai presscaller
//	TIM_TimeBaseStructure.TIM_ClockDivision = 0;												//clockdivision, diisi 0 ae
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;					//counter mode counter up
//	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;										//mode PWM1,
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
//	
//	TIM_OCInitStructure.TIM_Pulse = 0;
//	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
//	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);										//tim8 OC4 PRELOAD ENABLE
//	
//	TIM_OCInitStructure.TIM_Pulse = 0;
//	TIM_OC4Init(TIM3, &TIM_OCInitStructure);
//	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);										//tim4 OC2 PRELOAD ENABLE	
//	
//	TIM_ARRPreloadConfig(TIM3, ENABLE);
//	TIM_Cmd(TIM3, ENABLE);

//}

void GPIOInit(){

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3|GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure); 
	
}

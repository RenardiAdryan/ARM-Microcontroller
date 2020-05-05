#include "delay.h"

static __IO uint32_t sysTickCounter;

void DelayInit(void)
{
	SysTick_Config(SystemCoreClock/1000000);
}

void TimeTick_Decrement(void){
	if(sysTickCounter !=0x00){
		sysTickCounter--;
		}
}

void DelayUs(u32 n){
	sysTickCounter = n;
	while(sysTickCounter!=0){}
}

void delay_1ms(void){
	sysTickCounter = 1000;
	while(sysTickCounter!=0){}
}

void DelayMs(u32 n){
	while(n--){
	delay_1ms();
	}
}

void SysTick_Handler(){
	TimeTick_Decrement();
}
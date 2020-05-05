#include "stm32f10x.h"
	#include "stm32f10x_gpio.h"
	#include "stm32f10x_tim.h"
	#include "delay.h"
	#include "lcd16x2.h"
	#include <stdio.h>
	#include "stm32f10x_exti.h"
	#include "rotaryConf.h"
	#include "stdio.h"
	#include "stm32f10x_rcc.h"
	volatile uint8_t last_a,now_a;
	volatile uint8_t last_b,now_b;
	volatile int inc,dec;
	int value;char sValue[3];
void rotary_update(){
	
	now_a=(uint8_t)((GPIOB->IDR &GPIO_Pin_6)>> 6);
	now_b=(uint8_t)((GPIOB->IDR &GPIO_Pin_7)>> 7);
	
	inc = now_a ^ last_b;
	dec = now_b ^ last_a;
	
	if(inc)
	    {
	        value++;
	    }
	if(dec)
	    {
	        value--;
	    }
	
	last_a=now_a;
	last_b=now_b;
  
	if(value>=65535)  {value=65535;}
	if(value<0) {value=0;}
	
				
}

void EXTI9_5_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line6) | EXTI_GetITStatus(EXTI_Line7))
	{
		rotary_update();
		
		// Clear interrupt flag
		EXTI_ClearITPendingBit(EXTI_Line6);
		EXTI_ClearITPendingBit(EXTI_Line7);
		
	}
}
int lastValue;
 int main (void){
	 int value1;
	 	lcd16x2_init(LCD16X2_DISPLAY_ON_CURSOR_OFF_BLINK_OFF);
			DelayInit();
			rotaryInit();
	 GPIOInit();
		
	while(1){
//	lcd16x2_puts("ARAH PUTAR ");
	//if (value==lastValue){lcd16x2_puts(" stay");}
	//else if(value>lastValue){ lcd16x2_puts(" CW");}	   
	//else{ lcd16x2_puts(" CCW");} 
	//lastValue=value;
	
	sprintf(sValue,"%i",value);
	lcd16x2_gotoxy(0,1);
	lcd16x2_puts(sValue);
	DelayMs(10);
//	sprintf(sValue,"%i",lastValue);
	//lcd16x2_gotoxy(8,1);
	//lcd16x2_puts(sValue);
	//DelayMs(100);
	//lcd16x2_clrscr();
	 
		
				}
 }
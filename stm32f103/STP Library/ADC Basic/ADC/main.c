#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "lcd16x2.h"
#include "delay.h"
#include <stdio.h>
#include "ADC.h"

uint16_t adcValue;
char sAdcValue[5];

int main(void){
	ADC1_Init();
	lcd16x2_init(LCD16X2_DISPLAY_ON_CURSOR_OFF_BLINK_OFF);
	DelayInit();
	
	while (1){
		adcValue = ADC1_READ();
		sprintf(sAdcValue,"%i",adcValue);
		lcd16x2_puts("Nilai ADC adalah");
		lcd16x2_gotoxy(0,1);
		lcd16x2_puts(sAdcValue);
		DelayMs(100);
		lcd16x2_clrscr();
	}
}
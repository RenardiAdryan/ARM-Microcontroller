#include "stm32f10x.h"
#include "stdio.h"
#include "stm32f10x_tim.h"
#include "lcd16x2.h"
#include "delay.h"
#include "stm32f10x_gpio.h"
#include "config.h"
void TIM2_INT_Init(void);

uint16_t timervalue;
uint8_t detik,menit,jam;
char sTimervalue[2],time[3];

void TIM2_IRQHandler(){
if(TIM_GetITStatus(TIM2,TIM_IT_Update)){
	GPIOA->ODR ^= GPIO_Pin_3;
	GPIOA->ODR ^= GPIO_Pin_2;
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}


}

int main(void){
 
	GPIOInit();
	
	lcd16x2_init(LCD16X2_DISPLAY_ON_CURSOR_OFF_BLINK_OFF);
	
	DelayInit();
	
	TIM2Init();
	
	while(1){
		lcd16x2_puts("TIME : ");
		sprintf(time,"%i",jam);
		lcd16x2_puts(time);lcd16x2_puts(":");
		sprintf(time,"%i",menit);
		lcd16x2_puts(time);lcd16x2_puts(":");
		sprintf(time,"%i",detik);
		lcd16x2_puts(time);
	
	detik++;
        if(detik==60)
      {     detik=0;
            menit++; 
            
            if(menit==60){
                menit=0;
                jam++;     
                    if (jam==24){jam=0;}
                }
      }
	DelayMs(1000);
	lcd16x2_clrscr();
	}
	
}



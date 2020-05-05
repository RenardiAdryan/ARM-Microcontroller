#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "delay.h"
#include "lcd16x2.h"
#include <stdio.h>
#include "stm32f10x_rcc.h"
#include "config.h"
#include "stm32f10x_tim.h"
#include "delay.h"
#include "stm32f10x_USART.h"
int counter,counter1,prevcounter,prevcounter1,deCount;int posisi;
int last;
char sCounter[5];
void USART3_PutChar(char c);
void USART3_PutString(char *s);

void arah_linear_rotary(){int tik;
			
		counter= TIM_GetCounter(TIM4);
		counter1= TIM_GetCounter(TIM3);

	
		/*
		if(counter==prevcounter&&counter1<prevcounter1){
		lcd16x2_puts("Miring Kiri maju");DelayMs(900);
		}
		if(counter>prevcounter&&counter1==prevcounter1){
		lcd16x2_puts("Miring kanan maju");DelayMs(900);
		}*/
	
	  if(counter<prevcounter&&counter1<prevcounter1){
			lcd16x2_puts("kiri / ccw");
		}
		else if(counter>prevcounter&&counter1>prevcounter1){
			lcd16x2_puts("kanan / cw");
		}
		else if(counter>prevcounter&&counter1<prevcounter1){
		lcd16x2_puts("maju");
		}
		else if(counter<prevcounter&&counter1>prevcounter1){
		lcd16x2_puts("mundur");
		}
		else if(counter==prevcounter&&counter1==prevcounter1){
		lcd16x2_puts("BERHENTI");
		}

prevcounter=counter;
prevcounter1=counter1;
	
}


int  main (void){int lastCounter;
  DelayInit();
	lcd16x2_init(LCD16X2_DISPLAY_ON_CURSOR_OFF_BLINK_OFF);
	rotaryInit();
	USART3Init();
	GPIOInit();
	//USARTInterruptInit();
	GPIOA->BSRR = (1<<3);
	DelayInit();
	//TIM4->CNT=32767;
	//counter=TIM4->CNT;
	
	while(1){
		lcd16x2_clrscr();
	  /*counter= TIM_GetCounter(TIM4);
		counter1=TIM_GetCounter(TIM3);
		sprintf(sCounter,"%i ",counter);//lcd16x2_puts("Ec KIRI = ");
		USART3_PutString(sCounter);USART3_PutString("    ");
		
		sprintf(sCounter,"%i ",counter1);//lcd16x2_puts("Ec KIRI = ");
		USART3_PutString(sCounter);USART3_PutString("\n");*/
	  //lcd16x2_puts(sCounter);
		arah_linear_rotary();
		lcd16x2_gotoxy(11,0);
		sprintf(sCounter,"%i",counter);
		lcd16x2_puts(sCounter);
		lcd16x2_gotoxy(11,1);
		sprintf(sCounter,"%i",counter1);
		lcd16x2_puts(sCounter);
		//counter= TIM_GetCounter(TIM3);
		//sprintf(sCounter,"%i ",counter);
		//lcd16x2_gotoxy(0,1);lcd16x2_puts("Ec KANAN= ");
		//USART3_PutString(sCounter);USART3_PutString("\n");
		//lcd16x2_puts(sCounter);
		DelayMs(10);
//		
//	if(counter>=65400) TIM4->CNT=65535;
//	else if(counter<=100) TIM4->CNT=0;
//	
//	counter=TIM4->CNT;
//	posisi = counter - 32767 ;

//	sprintf(sCounter,"%i ",posisi);
//	lcd16x2_puts("POSISI  ");
//		
//	if (counter==lastCounter&&counter!=65535&&counter!=0){lcd16x2_puts(" STEADY ");}
//	else if(counter>lastCounter||counter==65535){ lcd16x2_puts(" CW");}	   
//	else if(counter<lastCounter||counter==0) {lcd16x2_puts(" CCW");} 
//		
//	lcd16x2_gotoxy(0,1);
//	lcd16x2_puts(sCounter);
//	sprintf(sCounter,"%i ",counter);lcd16x2_gotoxy(8,1);
//	lcd16x2_puts(sCounter);
//	DelayMs(80);lcd16x2_clrscr();
//	lastCounter = counter;
	}
}
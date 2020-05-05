#include "stm32f10x.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "delay.h"
#include "lcd16x2.h"
#include "config.h"
#include "stm32f10x_usart.h"



#define BUF_SIZE	16
char buf[BUF_SIZE];
void USART3_PutChar(char c);
void USART3_PutString(char *s);
void ledfunction();
char c;
int flag=0;
int count;
char indeks1[3];
char indeks2[3];
char indeks3[3];
int mikro1, mikro2, mikro3,i,j,last;

void USART3_IRQHandler()
{
	// Check if the USART3 receive interrupt flag was set
	if (USART_GetITStatus(USART3, USART_IT_RXNE))
	{
		// Index for receive buffer
		static uint8_t i = 0;
		
		// Read received char
		 c = USART_ReceiveData(USART3);
		// Read chars until newline
			if (c == '#') {flag = 1; count = 0;}
	
			else{
		
		count++;
		buf[count] = c;
		last = 1;
		
		
		if (flag==1 && c=='!'){
			
			for (i=1; i<4; i++) //jumlah mikro
			{
				
							for (j=0; j<10; j++) //jumlah data
				 {
							
										if (buf[j+last]==',' || buf[j+last]=='!') {
											last = last + j + 1;
											break;
										}
										switch (i) {
											case 1: indeks1[j] = buf[j+last];
											case 2: indeks2[j] = buf[j+last];
											case 3: indeks3[j] = buf[j+last];
										}
							
					}
							
							switch (i) {
								case 1: indeks1[j] = '\0';
								case 2: indeks2[j] = '\0';
								case 3: indeks3[j] = '\0';
							}
			}
			mikro1 = atoi (indeks1);				// --> data 1 = motor 1
			mikro2 = atoi (indeks2);				// --> data 2 = motor 2
			mikro3 = atoi (indeks3);				// --> data 3 = motor 3
			flag = 0; count = 0;indeks1[0]=NULL;indeks2[0]=NULL;indeks3[0]=NULL;
		}
	}
	}
}

int main(void)
{
	DelayInit();
	//lcd16x2_init(LCD16X2_DISPLAY_ON_CURSOR_OFF_BLINK_OFF);
	GPIOInit();
	
	// Initialize USART with receive interrupt
	USART3Init();
	USARTInterruptInit();
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
	while (1)
	{		
		//USART3_PutString("BUF = ");USART3_PutString(buf);USART3_PutString("\n");
		//lcd16x2_puts(buf);DelayMs(100);lcd16x2_clrscr();
		ledfunction(mikro1);		
	}
}

void tampilLed(int delayku){
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	DelayMs(delayku);
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
	DelayMs(delayku);
}

void ledfunction(int mode){
	switch(mode){
		case 10 :	tampilLed(100); break;
		case 11 :	tampilLed(200); break;
		case 12 :	tampilLed(500); break;
		case 13 :	tampilLed(1000); break;
		case 14 :	tampilLed(2000); break;
		case 15 :	tampilLed(5000); break;
	}
}


#include "stm32f10x.h"
#include "delay.h"
#include "config.h"
#include "stm32f10x_usart.h"
#include "string.h"
#include "lcd16x2.h"
#include "stdio.h"

#define BUF_SIZE	16
char buf[BUF_SIZE];
void USART3_PutChar(char c);
void USART3_PutString(char *s);


void USART3_IRQHandler()
{  
		
		
	// Check if the USART3 receive interrupt flag was set
	if (USART_GetITStatus(USART3, USART_IT_RXNE))
	{
		// Index for receive buffer
		static uint8_t i = 0;
		
		// Read received char
		char c = USART_ReceiveData(USART3);
		
		// Read chars until newline
		if (c != '\n')
		{
			// Concat char to buffer
			// If maximum buffer size is reached, then reset i to 0
			if (i < BUF_SIZE - 1)
			{
				buf[i] = c;
				i++;
			}
			else
			{
				buf[i] = c;
				i = 0;
			}
			
		}
		else
		{
			// Display received string to LCD
		lcd16x2_clrscr();
		lcd16x2_puts(buf);
			DelayMs(100);
			// Echo received string to USART3
			USART3_PutString(buf);
			USART3_PutChar('\n');
			
			// Clear buffer
			memset(&buf[0], 0, sizeof(buf));
			i = 0;
		}
		
	}
	//USART3_PutString(buf);USART3_PutString("\n");
	

}

int main(void)
{
	DelayInit();
	
	// Initialize USART with receive interrupt
	USART3Init();
	GPIOInit();
	USARTInterruptInit();

	//lcd16x2_init(LCD16X2_DISPLAY_ON_CURSOR_OFF_BLINK_OFF);
	while (1)
	{
		//lcd16x2_puts(buf);//USART3_PutChar('Y');
//		USART3_PutString("FACEBOOK\n");
		USART3_PutString("BUF = ");USART3_PutString(buf);USART3_PutString("\n");
//		DelayMs(100);
//		//USART3_PutChar('C');DelayMs(10);
//		//lcd16x2_blink_on();
		lcd16x2_puts(buf);DelayMs(10);lcd16x2_clrscr();
//		//lcd16x2_puts(buf);
	}
}



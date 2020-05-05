#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "lcd16x2.h"
 void delay(unsigned int nCount);
uint8_t custom_char[]={0x0E,0x1B,0x11,0x11,0x11,0x1F,0x1F};
 
int main(void)
{	
	
	lcd16x2_init(LCD16x2_DISPLAY_ON_CURSOR_OFF_BLINK_OFF);
	
	lcd16x2_create_custom_char(0,custom_char);
	
	while(1){
	lcd16x2_put_custom_char(0,0,0);
		lcd16x2_puts("Battery LOW");
		delay(500);
		lcd16x2clrscr();
		delay(500);
	}
}

void delay(unsigned int nCount)
	{
	    unsigned int i, j;
	    for (i = 0; i < nCount; i++)
	        for (j = 0; j < 0x2AFF; j++);
	}
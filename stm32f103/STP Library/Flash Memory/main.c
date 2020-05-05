#include <stm32f10x.h>
#include "stm32f10x_flash.h"
#include "stm32f10x_GPIO.h"
#include "stdio.h"
#include "stdlib.h"
#include "uc_memory.h"
#include "lcd20x4.h"
#include "config.h"

unsigned char x;
unsigned char y;
#define BUF 16
char buf[BUF];

uint16_t Address=0x0000;
uint8_t DataByte;
int main (void){

DelayInit();
GPIOInit();
lcd20x4_init(lcd20x4_DISPLAY_ON_CURSOR_OFF_BLINK_OFF);
FEE_Init();

//	FEE_WriteDataByte (Address,0x00);
	while(1){
	

	 if(!(GPIO_ReadInputData(GPIOB) & GPIO_Pin_5)){
   	DataByte=x++;
	  FEE_Erase ();
	  FEE_WriteDataByte (Address,DataByte);
		  
			
		}		
	 else if(!(GPIO_ReadInputData(GPIOB) & GPIO_Pin_4)){
	  DataByte=x--; 
		FEE_Erase ();
	  FEE_WriteDataByte (Address,DataByte);
		 
		
	 }
	 
	 y=FEE_ReadDataByte (Address);
	 sprintf(buf,"NON VOLATILE = %d",y);
	 lcd20x4_puts(buf); 
	 
	 lcd20x4_gotoxy(0,1);
	 sprintf(buf,"VOLATILE = %d",x);
	 lcd20x4_puts(buf); 
	 
	 
	 
	 //EEPROM_PutString(0x00F0,"AKU");
	 //y=FEE_ReadDataByte (Address);
	 //lcd20x4_gotoxy(0,2);
	 //sprintf(buf,"VOLATILE = %d",y);
	 //lcd20x4_puts(buf); 
	 
	 
		DelayMs(200);
	 lcd20x4_clrscr();
	 	
		

}
}

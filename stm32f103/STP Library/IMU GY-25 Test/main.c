#include "stm32f10x.h"
#include "stdio.h"
#include "string.h"
#include "config.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "delay.h"
#include "math.h"
#include "lcd20x4.h"
#define BUF 16
char buf[BUF];

void GPIOInit();
void USART3Init();
void USART3_PutChar(unsigned char c);
void USART3_PutString(unsigned char *s);
void Kirim1Byte(USART_TypeDef*USARTx, unsigned char x);

int YPR[3];
unsigned char Re_buf[8],counter=0;
unsigned char sign=0;
int dataYaw,dataPitch,dataRoll;


void resetImu(){
	DelayMs(2000);
	USART3_PutChar(0xA5);//Kirim1Byte(USART3,0xA5);
	USART3_PutChar(0x55);//Kirim1Byte(USART3,0x55);
	DelayMs(500);
	USART3_PutChar(0xA5);//Kirim1Byte(USART3,0xA5);
	USART3_PutChar(0x54);//Kirim1Byte(USART3,0x54);
	DelayMs(500);
	USART3_PutChar(0xA5);//Kirim1Byte(USART3,0xA5);
	USART3_PutChar(0x52);//Kirim1Byte(USART3,0x52);
}


void USART3_IRQHandler()
{  
	if (USART_GetITStatus(USART3, USART_IT_RXNE)) {                // --> read interrupt
		Re_buf[counter]=USART_ReceiveData(USART3);
		if(counter == 0 && Re_buf[0] != 0xAA) return; 
    counter++;
    if(counter == 8) {
			counter = 0;	
			sign = 1;
		}
	}
	
	
		if(sign==1 && Re_buf[0] == 0xAA && Re_buf[7] == 0x55) {sign = 0;
			YPR[0] = (Re_buf[1] << 8 | Re_buf[2])*0.01f;
			YPR[1] = (Re_buf[3] << 8 | Re_buf[4])*0.01f;
			YPR[2] = (Re_buf[5] << 8 | Re_buf[6])*0.01f;
			
			//Setelah nilai IMU 179 lalu melompat ke 475
			//range sudut 0-179 lalu 475-655 
			if (YPR[0] > 179)		{dataYaw = (655-YPR[0]);
																if(YPR[0]>475){dataYaw=-dataYaw;} //RANGE 0 <-> 180 || -179 <-> -1
													}
			else									dataYaw = YPR[0];
			
			if (YPR[1] > 179)		{dataPitch = (655-YPR[1]);
																if(YPR[0]>475){dataPitch=-dataPitch;} //RANGE 0 <-> 180 || -179 <-> -1
													}
			else									dataPitch = YPR[1];
			
			if (YPR[2] > 179)		{dataRoll = (655-YPR[2]);
																if(YPR[2]>475){dataRoll=-dataRoll;} //RANGE 0 <-> 180 || -179 <-> -1
													}
			else									dataRoll = YPR[2];
		
	}
	
	if(dataYaw<0) {dataYaw+=360;}
	if(dataPitch<0) dataPitch += 360;
	if(dataRoll<0) dataRoll += 360;

}

unsigned char 
 custom_char0[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F },
 custom_char1[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F },
 custom_char2[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F },
 custom_char3[] = { 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F },
 custom_char4[] = { 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F },
 custom_char5[] = { 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F },
 custom_char6[] = { 0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F },
 custom_char7[] = { 0x08, 0x04, 0x02, 0x01, 0x01, 0x02, 0x04, 0x08 };

 
void custom_charInit(){
	lcd20x4_create_custom_char(0,custom_char0);
	lcd20x4_create_custom_char(1,custom_char1);
	lcd20x4_create_custom_char(2,custom_char2);
	lcd20x4_create_custom_char(3,custom_char3);
	lcd20x4_create_custom_char(4,custom_char4);
	lcd20x4_create_custom_char(5,custom_char5);
	lcd20x4_create_custom_char(6,custom_char6);
	lcd20x4_create_custom_char(7,custom_char7);
} 





int i,j,dataYaw1,dataPitch1,dataRoll1;
int main (void){

	GPIOInit();
	USART3Init();
  USARTInterruptInit();
	DelayInit();
	lcd20x4_init(lcd20x4_DISPLAY_ON_CURSOR_OFF_BLINK_OFF);
	lcd20x4_clrscr();
	lcd20x4_puts("Calibrating...");lcd20x4_gotoxy(0,1);
	lcd20x4_puts("Don't move IMU");
	//resetImu();
	custom_charInit();
while(1){	
	lcd20x4_clrscr();
	lcd20x4_gotoxy(0,0);
	sprintf(buf,"%d",dataYaw);
	lcd20x4_puts("BISMILLAH ERSOW jUARA ok");
	//lcd20x4_puts(buf);
	DelayMs(100);
/*	
	lcd20x4_gotoxy(8,0);
	sprintf(buf,"%d",dataPitch);
	lcd20x4_puts("Pitc:");
	lcd20x4_puts(buf);
	
	lcd20x4_gotoxy(0,1);
	sprintf(buf,"%d",dataRoll);
	lcd20x4_puts("ROLL :");
	lcd20x4_puts(buf);
	*/
	
	
	/*//SCALLING DATA YAW,Pitch,Roll
	dataYaw1=(dataYaw*6)/359;
	//for(j=0;j<=dataYaw1;j++){
		for(i=0;i<=j;i++){
		lcd20x4_put_custom_char(i, 0, 7);
		}
		//DelayMs(90);
	//}
		
		dataPitch1=(dataPitch*6)/359;
	//for(j=0;j<=dataYaw1;j++){
		for(i=0;i<=dataPitch1;i++){
		lcd20x4_put_custom_char(i+8, 0, 7);
		}
		//DelayMs(110);
	//}
		
		dataRoll1=(dataRoll*6)/359;
	//for(j=0;j<=dataYaw1;j++){
		for(i=0;i<=dataRoll1;i++){
		lcd20x4_put_custom_char(i, 1, 7);
		}
		DelayMs(90);
	//}
	*/
	
	
	/*for(i=0;i<=7;i++){
	 lcd20x4_put_custom_char(i, 0, i);
	DelayMs(400);}lcd20x4_clrscr();DelayMs(1000);*/
	
	
	
	//USART1_PutString("USART 1 OK");USART1_PutString("\n");
	//USART3_PutString("USART 3 ok");USART3_PutString("\n");USART3_PutString("\n");
}
}

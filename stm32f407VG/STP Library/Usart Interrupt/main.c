#include "stm32f4xx.h"
#include "config.h"
#include "delay.h"
#include "stdio.h"
#include "stdlib.h"
#define BUF_SIZE	16
char buf[BUF_SIZE];
char xstring[BUF_SIZE];
int i;short flag;
void USART6_IRQHandler(void){
	char c=USART6_getchar();
  if(c=='#'){i=0;flag=1;}
	
	if (c != '!'&&flag==1) {
		buf[i] = c;
	  i++;
	}
	
	else{
		buf[i] = c;
		buf[i+1]='\0';
		
		//USART1_ftdi_Active();
	  //USART1_Puts(buf);
		//USART_Cmd(USART1,DISABLE);
		
		//USART1_IMU_Active();
	  //USART1_Puts(buf);
		//USART_Cmd(USART1,DISABLE);
		flag=0;
   }

 }

 
 int YPR[3];
unsigned char Re_buf[8],counter=0;
unsigned char sign=0;
int dataYaw,dataPitch,dataRoll;

 
 void USART1_IRQHandler(void){
//lcd_string("INTERUPT OK");	
	if (USART_GetITStatus(USART1, USART_IT_RXNE)) {   
	//	lcd_gotoxy(0,0);
			// --> read interrupt
		Re_buf[counter]=USART_ReceiveData(USART1);
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
		
													
													
	
	//if(dataYaw<0) {dataYaw+=360;}
	if(dataPitch<0) dataPitch += 360;
	if(dataRoll<0) dataRoll += 360;
													sprintf(xstring,"%d",dataYaw);
													USART6_Puts(xstring);
						
													USART6_Puts("\n");
													

	}

}

void resetImu(){
  DelayMs(2000);
	USART1_PutChar(0xA5);//Kirim1Byte(USART3,0xA5);
	USART1_PutChar(0x55);//Kirim1Byte(USART3,0x55);
	DelayMs(500);
	USART1_PutChar(0xA5);//Kirim1Byte(USART3,0xA5);
	USART1_PutChar(0x54);
	//Kirim1Byte(USART3,0x54);
	DelayMs(500);
	USART1_PutChar(0xA5);//Kirim1Byte(USART3,0xA5);
	USART1_PutChar(0x52);//Kirim1Byte(USART3,0x52);
}

/*

void USART1_IRQHandler(void){
	char c=USART1_getchar();
  if(c=='#'){i=0;flag=1;}
	
	if (c != '!'&&flag==1) {
		buf[i] = c;
	  i++;
	}
	
	else{
		buf[i] = c;
		buf[i+1]='\0';
	  USART3_Puts(buf);
		flag=0;
   }

 }
*/
int main(){
		GPIOInit();
		InteruptInit();
		USARTInit();
	  DelayInit();
	//USART1_IMU_Active();
	resetImu();
		while(1){
		//NOP
		//	GPIO_SetBits(GPIOD,GPIO_Pin_12);
		//USART3_Puts("#100,10,-25,-25!");
	  //USART1_ftdi_Active();
	  //USART6_Puts("#100,10,-25,-25!");
		//USART_Cmd(USART1,DISABLE);

		//USART1_PutChar(0x31);
	  //USART1_Puts("#100,10,-25,-25!");
		//USART_Cmd(USART1,DISABLE);
		}	
}

///tx=C6
///rx=c7

//amphenaol 
//Rx=c11
//tx=c10
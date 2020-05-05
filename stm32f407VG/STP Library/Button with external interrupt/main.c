#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_exti.h"

#include "stm32f4xx_SYSCFG.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"
#include "delay.h"
#include "stdbool.h"
#include "stm32f4xx_tim.h"
#include "config.h"


void delayloop(int ms){
int i,j,k;
for(k=0;k<=ms;k++){
	for(i=0;i<=168;i++){
	for(j=0;j<=1000;j++){}}}//168000=1ms Asusmsi clock nya adalah 168Mhz
}


int flag1;
bool menu=true;
void EXTI9_5_IRQHandler(){

 if(EXTI_GetITStatus(EXTI_Line6)==SET){
	menu^=true;
	delayloop(3);//To Eliminate debounce delay 3ms
	EXTI_ClearITPendingBit(EXTI_Line6);
    }
}






void button_scan(){
	

	
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0){
	while(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)){}flag1=0;}
	
	else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==0){
	while(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)){}flag1=1;;}
	
	else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0){
	while(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)){}flag1=2;}
	
	else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0){
	while(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)){}flag1=3;}
	
	
	else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0){
	while(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)){}flag1=4;}
	
	
	else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0){
	while(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)){}flag1=5;}

	else {flag1=9;};
	
	DELAY_Us(3);

}




int main(){

GPIOInit();
		DELAY_Init();	
EXTI_ButtonConfig();
InterruptInit();

while(1){
	if(menu==true){
button_scan();
	
	if(flag1==0){GPIO_ToggleBits(GPIOD,GPIO_Pin_13);}
	else if(flag1==1){GPIO_ToggleBits(GPIOD,GPIO_Pin_14);}
	else if(flag1==2){GPIO_ToggleBits(GPIOD,GPIO_Pin_15);}
	
	else if(flag1==3){GPIO_ToggleBits(GPIOD,GPIO_Pin_13);}
	else if(flag1==4){GPIO_ToggleBits(GPIOD,GPIO_Pin_14);}
	else if(flag1==5){}
	else {}
		GPIO_SetBits(GPIOD,GPIO_Pin_12);
	}	
	else if(menu==false){
	GPIO_ResetBits(GPIOD,GPIO_Pin_12);
	}
	
	
}


	
	
}

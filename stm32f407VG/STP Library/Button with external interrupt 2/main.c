#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_exti.h"
#include "config.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

void delayloop(int ms){
int i,j,k;
for(k=0;k<=ms;k++){
	for(i=0;i<=168;i++){
	for(j=0;j<=1000;j++){}}}//168000=1ms Asusmsi clock nya adalah 168Mhz
}


bool menu=true;
void EXTI9_5_IRQHandler(){

 if(EXTI_GetITStatus(EXTI_Line6)){
  GPIO_SetBits(GPIOD,GPIO_Pin_12);
	delayloop(100);//To Eliminate debounce delay 3ms
	EXTI_ClearITPendingBit(EXTI_Line6);
    }
}



int main(){
GPIOInit();
EXTI_ButtonConfig();
	InterruptInit();
while(1){
GPIO_ResetBits(GPIOD,GPIO_Pin_12);

}
}
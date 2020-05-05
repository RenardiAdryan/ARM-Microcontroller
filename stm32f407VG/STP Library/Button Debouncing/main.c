#include "stm32f4xx.h"
#include "config.h"
#include "delay.h"
#include "GlobalVariable.h"

int isButtonPressed(int pin)//Function to eliminate debouncing
{
  if(!GPIO_ReadInputDataBit(ButtonPort,pin))
  {
    DELAY_Ms(5);
    if	   (!GPIO_ReadInputDataBit(ButtonPort,pin)) return 1;
    else if(GPIO_ReadInputDataBit(ButtonPort,pin)) return 0;
  }
	else return 0;
}

int main(){

	GPIOInit();
	
		while(1){
			if(isButtonPressed(pin_A0)){
				//DO THE JOB;
				}

			}

}
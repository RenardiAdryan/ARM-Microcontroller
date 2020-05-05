#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
void delay(unsigned int nCount);
GPIO_InitTypeDef GPIO_InitStruct;
char statusBits[5];
int main(void){
	//enable clock for GPIOB
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
		
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	while(1){
	//jika button on PB12 di tekan 
		
		/*if(!(GPIO_ReadInputData(GPIOB) & GPIO_Pin_12)||!(GPIO_ReadInputData(GPIOB) & GPIO_Pin_13)){
		 
			GPIO_SetBits(GPIOA,GPIO_Pin_2);
		  GPIO_SetBits(GPIOA,GPIO_Pin_3);		
			
		}
		else 
		{
		  GPIO_ResetBits(GPIOA,GPIO_Pin_2);
			GPIO_ResetBits(GPIOA,GPIO_Pin_3);
		}*/
		statusBits[0]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1);
		statusBits[1]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0);
		statusBits[2]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4);
		statusBits[3]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5);
		
	}
		
}

void delay(unsigned int nCount)
	{
	    unsigned int i, j;
	    for (i = 0; i < nCount; i++)
	        for (j = 0; j < 0x2AFF; j++);
	}
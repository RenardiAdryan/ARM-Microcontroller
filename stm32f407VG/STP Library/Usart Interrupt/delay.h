#ifndef __DELAY_H
#define __DELAY_H
#include "stm32f4xx.h"

void DelayInit(void);
void TimerTick_Decrement(void);
void DelayUs(u32 n);
void delay_1ms(void);
void DelayMs(u32 n);

#endif
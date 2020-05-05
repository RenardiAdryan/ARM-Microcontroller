#ifndef __CONFIG_H
#define __CONFIG_H

extern void GPIOInit();
extern void InteruptInit();
extern void USARTInit();
extern uint8_t USART6_getchar(void);
extern void USART6_Puts(char *s);
extern void USART6_PutChar(uint8_t c);

extern uint8_t USART3_getchar(void);
extern void USART3_Puts(char *s);
extern void USART3_PutChar(uint8_t x);

extern uint8_t USART1_getchar(void);
extern void USART1_Puts(char *s);
extern void USART1_PutChar(uint8_t x);

extern void USART1_ftdi_Active();
extern void USART1_IMU_Active();
#endif
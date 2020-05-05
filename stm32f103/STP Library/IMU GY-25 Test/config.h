#ifndef __CONF_H
#define __CONF_H

extern void GPIOInit();
extern void USART3Init();
extern void USARTInterruptInit();
extern void USART3_PutChar(unsigned char c);
extern void USART3_PutString(unsigned char *s);
extern void Kirim1Byte(USART_TypeDef*USARTx, unsigned char x);
#endif
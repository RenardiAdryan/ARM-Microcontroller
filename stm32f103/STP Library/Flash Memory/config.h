#ifndef __CONF_H
#define __CONF_H

extern void GPIOInit();
extern void USART3Init();
extern void USARTInterruptInit();
extern void USART3_PutChar(unsigned char c);
extern void USART3_PutString(unsigned char *s);
extern void Kirim1Byte(USART_TypeDef*USARTx, unsigned char x);
extern void EEPROM_PutString(uint16_t Address,unsigned char *s);
#endif
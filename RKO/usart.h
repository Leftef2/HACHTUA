#ifndef _USART_H_
#define _USART_H_
#include <stm32f4xx.h>
void init_USART(int mod,char* Pin1,char* Pin2);
void send_usart(int mod,unsigned char d);

#endif

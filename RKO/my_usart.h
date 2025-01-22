#ifndef MY_USART_H
#define MY_USART_H
#include <stm32f4xx.h>
void USART_setup(char* Pin1,char* Pin2);
void write_usart(char d);
int USART_faied(void);
int USART_ready(void);
#endif
#ifndef MY_FUNCTIONS_H
#define MY_FUNCTIONS_H

#include <stm32f4xx.h>
int getNum(char* str);
void menu_debounce(void);
void init(void);
void Shortbuzz(void);
void send_Line1(char* str);
void send_Line2(char* str);
#endif
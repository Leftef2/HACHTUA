#ifndef MY_DAC_H
#define MY_DAC_H
#include <stm32f4xx.h>
void DAC_SETUP(char* str, int dac);
void DACstartconv(int dac);
int DACout(int dac);

#endif
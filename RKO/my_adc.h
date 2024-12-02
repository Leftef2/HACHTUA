#ifndef MY_ADC_H
#define MY_ADC_H
#include <stm32f4xx.h>
void ADC_SETUP(char* str, int adc);
void ADCstartconv(int adc);
int ADCout(int adc);
#endif
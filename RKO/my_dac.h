#ifndef MY_DAC_H
#define MY_DAC_H
#include <stm32f4xx.h>
#include <math.h>

void Init_DAC2(void);
void DC_level(void);
void Ramp_Output (void);
void Complex_Output (void);
void Square_Output (void);
void Sin_Output (void);
void swatch (float);
#endif
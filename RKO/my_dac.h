#ifndef MY_DAC_H
#define MY_DAC_H
#include <stm32f4xx.h>
#include <math.h>

void init_DAC(void);
void send_dac(int a);
//void DC_level(void);
void Ramp_Output (void);
//void Square_Output (void);
//void Sin_Output (void);
//void swatch (float);
#endif
#ifndef _TIMERS_H_
#define _TIMERS_H_
#include <stm32f4xx.h>
void TIM2_IRQHandler(void);			//TIMER 2 INTERRUPT SERVICE ROUTINE
void timer_init(void);

#endif
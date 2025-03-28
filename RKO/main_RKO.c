#include <stm32f429xx.h>		//INCLUDE THE HEADER FILE FOR THIS MCU FAMILY
#include "my_led.h"
#include "timers.h"
#include "my_dac.h"



int main(void){
	init_DAC();
	timer_init();
	send_dac((1000));
}
int Counter;

int Ratio=10;
void TIM2_IRQHandler(void){
	TIM2->SR&=~TIM_SR_UIF;//clear interrupt flag in status register
	Counter++;
	if(Counter==1){
		send_dac((0000));
	}
	else{
		send_dac(0000);
	}
	if(Counter>Ratio){
		Counter=0;
	}
}
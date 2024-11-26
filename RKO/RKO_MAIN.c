#include <stm32f429xx.h>		//INCLUDE THE HEADER FILE FOR THIS MCU FAMILY
#include <core_cm4.h>
void delay (void)
{	
	volatile unsigned int i;		//create variable
	for (i=0; i<1000000; i++);	//WAIT count to 1 million 
}
void ADC_SETUP(void){
	ADC->CR2|=(1<<0);
	ADC->CR2|=(1<<30);
	ADC->CR1&=(00<<24);
	ADC->CR1&=(1<<9);
	ADC->CR1&=(1<<23);
	RCC->APB2ENR|=(1<<8);
}
void main(void){
	uint32_t ADC_DATA[1000];
}
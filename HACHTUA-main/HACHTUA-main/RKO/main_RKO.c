#include <stm32f429xx.h>		//INCLUDE THE HEADER FILE FOR THIS MCU FAMILY
#include <core_cm4.h>
void delay (void)
{	
	volatile unsigned int i;		//create variable
	for (i=0; i<1000000; i++);	//WAIT count to 1 million 
}
void ADC_SETUP(void){
	ADC2->CR2|=(1<<0);
	ADC2->CR2|=(1<<30);
	

}
void LED_INIT (void)
{
	//ENABLE PORT(S)
	//RCC->AHB1ENR |= 0x02;						//use label defined in stm32f4.h instead of hex value: easier to read and change
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;	//ONLY GPIO B clock enable
	
	//CONFIGURE PORT:GPIOB  PIN:0 TO OUTPUT for LED1
	GPIOB->MODER |= 0x01;						//ONLY set  GPIOB0
	// the above assumes that bit 1 is to zero
	GPIOB->MODER &= ~0x02;					//ONLY clear GPIOB1
}	
void LED_ON (void)
{
			GPIOB->ODR |= 1;							//ONLY TURN LED ON
}

void LED_OFF (void)
{
			GPIOB->ODR &= ~1;							//ONLY TURN LED ON
}
int main(void){
	ADC_SETUP();
	LED_INIT();
	LED_ON();
	
}

#include <stm32f429xx.h>		//INCLUDE THE HEADER FILE FOR THIS MCU FAMILY
													//this file contains the definitions for register addresses and values etc...


int main(void)					// MAIN PROGRAM
{
	volatile unsigned int i;		//create variable i
	
	//ENABLE PORT(S)
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIOBEN;	//GPIO C and B clock enabled - B is used for LEDs and C for the button
	
	//CONFIGURE PORT:GPIOB  PIN:0 TO OUTPUT for LED1
	GPIOB->MODER |= 1<<0;	//set new pin functions on GPIOB0 (green LED)
	GPIOB->MODER |= 1<<7; //sets the pin functions for red LED (pin 29 & 28)
	GPIOB->MODER |= 0x4000; //Blue LED (pin 7(15 & 14))
	//GPIOC->MODER |= 0x0;
	while(1){		//ENTER 'FOREVER' LOOP - THIS LOOP WILL NEVER EXIT
		
	if(GPIOC->IDR	& (1<<13))		//checks the current state of pins on GPIOC and checks if register 13 is pressed "high"
	{
		GPIOB->BSRR = 0x4081;								//TURN LEDs ON
	} else{
		GPIOB->BSRR = 0x40810000;								//TURN LEDs OFF
	}
	}
}


//Note - I have used hex codes for register/pin identification. Converting them to binary might make this easier to understand.F
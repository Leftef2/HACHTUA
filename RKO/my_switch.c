#include "my_switch.h"
#include "my_functions.h"
#include <stdlib.h>

void createSwitch(char* pin){//creates function
	if(pin[1]=='A'){//check which GPIO
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;//enable the port clock
		GPIOA->MODER&=~(3u<<getNum(pin));//sets mode to input
		GPIOA->PUPDR&=~(3u<<2*getNum(pin));//sets 00 in PUPDR register
		GPIOA->PUPDR|=(2u<<2*getNum(pin));//sets 10 in PUPDR register for pull down resistor
		GPIOA->OTYPER&=~(1<<getNum(pin));//sets output to Output push-pull (reset state)
		GPIOA->OSPEEDR|=(3u<<getNum(pin));//sets speed of read to high

	}
	if(pin[1]=='B'){//check which GPIO
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN;//enable the port clock
		GPIOB->MODER&=~(3u<<getNum(pin));//sets mode to input
		GPIOB->PUPDR&=~(3u<<2*getNum(pin));//sets 00 in PUPDR register
		GPIOB->PUPDR|=(2u<<2*getNum(pin));//sets 10 in PUPDR register for pull down resistor
		GPIOB->OTYPER&=~(1<<getNum(pin));//sets output to Output push-pull (reset state)
		GPIOB->OSPEEDR|=(3u<<getNum(pin));//sets speed of read to high
	}
	if(pin[1]=='C'){//check which GPIO
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOCEN;//enable the port clock
		GPIOC->MODER&=~(3u<<getNum(pin));//sets mode to input
		GPIOC->PUPDR&=~(3u<<2*getNum(pin));//sets 00 in PUPDR register
		GPIOC->PUPDR|=(2u<<2*getNum(pin));//sets 10 in PUPDR register for pull down resistor
		GPIOC->OTYPER&=~(1<<getNum(pin));//sets output to Output push-pull (reset state)
		GPIOC->OSPEEDR|=(3u<<getNum(pin));//sets speed of read to high
	}
	if(pin[1]=='D'){//check which GPIO
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIODEN;//enable the port clock
		GPIOD->MODER&=~(3u<<getNum(pin));//sets mode to input
		GPIOD->PUPDR&=~(3u<<2*getNum(pin));//sets 00 in PUPDR register
		GPIOD->PUPDR|=(2u<<2*getNum(pin));//sets 10 in PUPDR register for pull down resistor
		GPIOD->OTYPER&=~(1<<getNum(pin));//sets output to Output push-pull (reset state)
		GPIOD->OSPEEDR|=(3u<<getNum(pin));//sets speed of read to high
	}
	if(pin[1]=='E'){//check which GPIO
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOEEN;//enable the port clock
		GPIOE->MODER&=~(3u<<getNum(pin));//sets mode to input
		GPIOE->PUPDR&=~(3u<<2*getNum(pin));//sets 00 in PUPDR register
		GPIOE->PUPDR|=(2u<<2*getNum(pin));//sets 10 in PUPDR register for pull down resistor
		GPIOE->OTYPER&=~(1<<getNum(pin));//sets output to Output push-pull (reset state)
		GPIOE->OSPEEDR|=(3u<<getNum(pin));//sets speed of read to high
	}
	if(pin[1]=='F'){//check which GPIO
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOFEN;//enable the port clock
		GPIOF->MODER&=~(3u<<getNum(pin));//sets mode to input
		GPIOF->PUPDR&=~(3u<<2*getNum(pin));//sets 00 in PUPDR register
		GPIOF->PUPDR|=(2u<<2*getNum(pin));//sets 10 in PUPDR register for pull down resistor
		GPIOF->OTYPER&=~(1<<getNum(pin));//sets output to Output push-pull (reset state)
		GPIOF->OSPEEDR|=(3u<<getNum(pin));//sets speed of read to high
	}
	if(pin[1]=='G'){//check which GPIO
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOGEN;//enable the port clock
		GPIOG->MODER&=~(3u<<getNum(pin));//sets mode to input
		GPIOG->PUPDR&=~(3u<<2*getNum(pin));//sets 00 in PUPDR register
		GPIOG->PUPDR|=(2u<<2*getNum(pin));//sets 10 in PUPDR register for pull down resistor
		GPIOG->OTYPER&=~(1<<getNum(pin));//sets output to Output push-pull (reset state)
		GPIOG->OSPEEDR|=(3u<<getNum(pin));//sets speed of read to high
	}
}
int Switch(char* pin){//creates a function that returns 1 if the button is pressed
	if(pin[1]=='A'){
		if(GPIOA->IDR&(1<<getNum(pin))){//gets the result at that GPIO register at that pin
			return 1;
		}
		else{
			return 0;
		}
	}
	else if(pin[1]=='B'){
		if(GPIOB->IDR&(1<<getNum(pin))){//gets the result at that GPIO register at that pin
			return 1;
		}
		else{
			return 0;
		}
	}
	else if(pin[1]=='C'){
		if(GPIOC->IDR&(1<<getNum(pin))){//gets the result at that GPIO register at that pin
			return 1;
		}
		else{
			return 0;
		}
	}
	else if(pin[1]=='D'){
		if(GPIOD->IDR&(1<<getNum(pin))){//gets the result at that GPIO register at that pin
			return 1;
		}
		else{
			return 0;
		}
	}
	else if(pin[1]=='E'){
		if(GPIOE->IDR&(1<<getNum(pin))){//gets the result at that GPIO register at that pin
			return 1;
		}
		else{
			return 0;
		}
	}
	else if(pin[1]=='F'){
		if(GPIOF->IDR&(1<<getNum(pin))){//gets the result at that GPIO register at that pin
			return 1;
		}
		else{
			return 0;
		}
	}
	else if(pin[1]=='G'){
		if(GPIOG->IDR&(1<<getNum(pin))){//gets the result at that GPIO register at that pin
			return 1;
		}
		else{
			return 0;
		}
	}
	else{
		return 0;
	}
}
	

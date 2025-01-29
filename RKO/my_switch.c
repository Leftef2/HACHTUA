#include "my_switch.h"
#include "my_functions.h"
#include <stdlib.h>

void createSwitch(char* pin){//creates function
	if(pin[1]=='A'){//check which GPIO
		//enable the port clock
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;
		GPIOA->PUPDR&=~(3u<<2*getNum(pin));//sets 00 in PUPDR register
		GPIOA->PUPDR|=(2u<<2*getNum(pin));//sets 10 in PUPDR register for pull down resistor
	}
	if(pin[1]=='B'){//check which GPIO
		//enable the port clock
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN;
		GPIOB->PUPDR&=~(3u<<2*getNum(pin));//sets 00 in PUPDR register
		GPIOB->PUPDR|=(2u<<2*getNum(pin));//sets 10 in PUPDR register for pull down resistor
	}
	if(pin[1]=='C'){//check which GPIO
		//enable the port clock
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOCEN;
		GPIOC->PUPDR&=~(3u<<2*getNum(pin));//sets 00 in PUPDR register
		GPIOC->PUPDR|=(2u<<2*getNum(pin));//sets 10 in PUPDR register for pull down resistor
	}
	if(pin[1]=='D'){//check which GPIO
		//enable the port clock
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIODEN;
		GPIOD->PUPDR&=~(3u<<2*getNum(pin));//sets 00 in PUPDR register
		GPIOD->PUPDR|=(2u<<2*getNum(pin));//sets 10 in PUPDR register for pull down resistor
	}
	if(pin[1]=='E'){//check which GPIO
		//enable the port clock
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOEEN;
		GPIOE->PUPDR&=~(3u<<2*getNum(pin));//sets 00 in PUPDR register
		GPIOE->PUPDR|=(2u<<2*getNum(pin));//sets 10 in PUPDR register for pull down resistor
	}
	if(pin[1]=='F'){//check which GPIO
		//enable the port clock
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOFEN;
		GPIOF->PUPDR&=~(3u<<2*getNum(pin));//sets 00 in PUPDR register
		GPIOF->PUPDR|=(2u<<2*getNum(pin));//sets 10 in PUPDR register for pull down resistor
	}
	if(pin[1]=='G'){//check which GPIO
		//enable the port clock
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOGEN;
		GPIOG->PUPDR&=~(3u<<2*getNum(pin));//sets 00 in PUPDR register
		GPIOG->PUPDR|=(2u<<2*getNum(pin));//sets 10 in PUPDR register for pull down resistor
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
	if(pin[1]=='B'){
		if(GPIOB->IDR&(1<<getNum(pin))){//gets the result at that GPIO register at that pin
			return 1;
		}
		else{
			return 0;
		}
	}
	if(pin[1]=='C'){
		if(GPIOC->IDR&(1<<getNum(pin))){//gets the result at that GPIO register at that pin
			return 1;
		}
		else{
			return 0;
		}
	}
	if(pin[1]=='D'){
		if(GPIOD->IDR&(1<<getNum(pin))){//gets the result at that GPIO register at that pin
			return 1;
		}
		else{
			return 0;
		}
	}
	if(pin[1]=='E'){
		if(GPIOE->IDR&(1<<getNum(pin))){//gets the result at that GPIO register at that pin
			return 1;
		}
		else{
			return 0;
		}
	}
	if(pin[1]=='F'){
		if(GPIOF->IDR&(1<<getNum(pin))){//gets the result at that GPIO register at that pin
			return 1;
		}
		else{
			return 0;
		}
	}
	if(pin[1]=='G'){
		if(GPIOG->IDR&(1<<getNum(pin))){//gets the result at that GPIO register at that pin
			return 1;
		}
		else{
			return 0;
		}
	}
}
	

#include "my_led.h"
#include "my_functions.h"


void LED_SETUP(char* str){
	if(str[1]=='A'){//gets the second letter of the input "PB0">B
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;//enables GPIOB clock
		GPIOA->MODER |= (1<<(getNum(str)*2));//sets the 1 of 01 to the appropriate MODER
		GPIOA->MODER &= ~(0<<((getNum(str)*2)+1));//sets the 0 of 01 to the appropriate MODER
		GPIOA->OTYPER|=(1<<getNum(str));//sets 1 for output open drain
		GPIOA->OSPEEDR|=(3u<<(getNum(str)*2));//sets 11 for high speed reading
		GPIOA->PUPDR&=~(3u<<(getNum(str)*2));//sets 00 for not pull up or pull down since its an output
	}
	if(str[1]=='B'){
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;//enables GPIOB clock
		GPIOB->MODER |= (1<<(getNum(str)*2));//sets the 1 of 01 to the appropriate MODER
		GPIOB->MODER &= ~(0<<((getNum(str)*2)+1));//sets the 0 of 01 to the appropriate MODER
		GPIOB->OTYPER&=~(0<<getNum(str));//sets 1 for output open drain
		GPIOB->OSPEEDR|=(3u<<(getNum(str)*2));//sets 11 for high speed reading
		GPIOB->PUPDR&=~(3u<<(getNum(str)*2));//sets 00 for not pull up or pull down since its an output
	}
	if(str[1]=='C'){
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;//enables GPIOB clock
		GPIOC->MODER |= (1<<(getNum(str)*2));//sets the 1 of 01 to the appropriate MODER
		GPIOC->MODER &= ~(0<<((getNum(str)*2)+1));//sets the 0 of 01 to the appropriate MODER
		GPIOC->OTYPER|=(1<<getNum(str));//sets 1 for output open drain
		GPIOC->OSPEEDR|=(3u<<(getNum(str)*2));//sets 11 for high speed reading
		GPIOC->PUPDR&=~(3u<<(getNum(str)*2));//sets 00 for not pull up or pull down since its an output
	}
	if(str[1]=='D'){
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;//enables GPIOB clock
		GPIOD->MODER |= (1<<(getNum(str)*2));//sets the 1 of 01 to the appropriate MODER
		GPIOD->MODER &= ~(0<<((getNum(str)*2)+1));//sets the 0 of 01 to the appropriate MODER
		GPIOD->OTYPER|=(1<<getNum(str));//sets 1 for output open drain
		GPIOD->OSPEEDR|=(3u<<(getNum(str)*2));//sets 11 for high speed reading
		GPIOD->PUPDR&=~(3u<<(getNum(str)*2));//sets 00 for not pull up or pull down since its an output
	}
	if(str[1]=='E'){
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;//enables GPIOB clock
		GPIOE->MODER |= (1<<(getNum(str)*2));//sets the 1 of 01 to the appropriate MODER
		GPIOE->MODER &= ~(0<<((getNum(str)*2)+1));//sets the 0 of 01 to the appropriate MODER
		GPIOE->OTYPER|=(1<<getNum(str));//sets 1 for output open drain
		GPIOE->OSPEEDR|=(3u<<(getNum(str)*2));//sets 11 for high speed reading
		GPIOE->PUPDR&=~(3u<<(getNum(str)*2));//sets 00 for not pull up or pull down since its an output
	}
	if(str[1]=='F'){
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;//enables GPIOB clock
		GPIOF->MODER |= (1<<(getNum(str)*2));//sets the 1 of 01 to the appropriate MODER
		GPIOF->MODER &= ~(0<<((getNum(str)*2)+1));//sets the 0 of 01 to the appropriate MODER
		GPIOF->OTYPER|=(1<<getNum(str));//sets 1 for output open drain
		GPIOF->OSPEEDR|=(3u<<(getNum(str)*2));//sets 11 for high speed reading
		GPIOF->PUPDR&=~(3u<<(getNum(str)*2));//sets 00 for not pull up or pull down since its an output
	}
}	
void LED_ON(char* str){
	if(str[1]=='A'){
		GPIOA->BSRR|=(1<<getNum(str));//gives 1 to the right pin of BSRR
	}
	if(str[1]=='B'){
		GPIOB->BSRR|=(1<<getNum(str));//gives 1 to the right pin of BSRR
	}
	if(str[1]=='C'){
		GPIOC->BSRR|=(1<<getNum(str));//gives 1 to the right pin of BSRR
	}
	if(str[1]=='E'){
		GPIOE->BSRR|=(1<<getNum(str));//gives 1 to the right pin of BSRR
	}
	if(str[1]=='F'){
		GPIOF->BSRR|=(1<<getNum(str));//gives 1 to the right pin of BSRR
	}
}
void LED_OFF(char* str){
	if(str[1]=='A'){
		GPIOA->BSRR|=(1<<(16+getNum(str)));//gives 1 reset register of BSRR
	}
	if(str[1]=='B'){
		GPIOB->BSRR|=(1<<(16+getNum(str)));//gives 1 reset register of BSRR
	}
	if(str[1]=='C'){
		GPIOC->BSRR|=(1<<(16+getNum(str)));//gives 1 reset register of BSRR
	}
	if(str[1]=='E'){
		GPIOE->BSRR|=(1<<(16+getNum(str)));//gives 1 reset register of BSRR
	}
	if(str[1]=='F'){
		GPIOF->BSRR|=(1<<(16+getNum(str)));
	}
}
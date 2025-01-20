#include <stm32f429xx.h>
#include <stdlib.h>
#include "my_led.h"

int getNum(char* str){
	if(sizeof(str)==5){
		return (atoi(&str[2])*10)+atoi(&str[3]);
	}
	else if(atoi(&str[2])==0){
		return 0;
	}
	else{
		return atoi(&str[2]);
	}
}

void LED_SETUP(char* str){
	if(str[1]=='A'){//gets the second letter of the input "PB0">B
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;//enables GPIOB clock
		GPIOA->MODER |= (1<<(getNum(str)*2));//sets the 1 of 01 to the appropriate MODER
		GPIOA->MODER &= ~(0<<((getNum(str)*2)+1));//sets the 0 of 01 to the appropriate MODER
	}
	if(str[1]=='B'){
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
		GPIOB->MODER |= (1<<(getNum(str)*2));
		GPIOB->MODER &= ~(0<<((getNum(str)*2)+1));
	}
	if(str[1]=='C'){
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
		GPIOC->MODER |= (1<<(getNum(str)*2));
		GPIOC->MODER &= ~(0<<((getNum(str)*2)+1));
	}
	if(str[1]=='D'){
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
		GPIOD->MODER |= (1<<(getNum(str)*2));
		GPIOD->MODER &= ~(0<<((getNum(str)*2)+1));
	}
	if(str[1]=='E'){
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
		GPIOE->MODER |= (1<<(getNum(str)*2));
		GPIOE->MODER &= ~(0<<((getNum(str)*2)+1));
	}
	if(str[1]=='F'){
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
		GPIOF->MODER |= (1<<(getNum(str)*2));
		GPIOF->MODER &= ~(0<<((getNum(str)*2)+1));
	}
}	
void LED_ON(char* str){
	if(str[1]=='A'){
		GPIOA->ODR |=(1<<getNum(str));//gives 1 to the right pin and right GPIO
	}
	if(str[1]=='B'){
		GPIOB->ODR |=(1<<getNum(str));
	}
	if(str[1]=='C'){
		GPIOC->ODR |=(1<<getNum(str));
	}
	if(str[1]=='E'){
		GPIOE->ODR |=(1<<getNum(str));
	}
	if(str[1]=='F'){
		GPIOF->ODR |=(1<<getNum(str));
	}
}
void LED_OFF(char* str){
	if(str[1]=='A'){
		GPIOA->ODR &=~(1<<getNum(str));//gives 1 to the right pin and right GPIO
	}
	if(str[1]=='B'){
		GPIOB->ODR &=~(1<<getNum(str));
	}
	if(str[1]=='C'){
		GPIOC->ODR &=~(1<<getNum(str));
	}
	if(str[1]=='E'){
		GPIOE->ODR &=~(1<<getNum(str));
	}
	if(str[1]=='F'){
		GPIOF->ODR &=~(1<<getNum(str));
	}
}
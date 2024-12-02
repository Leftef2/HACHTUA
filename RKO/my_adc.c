#include <stm32f429xx.h>
#include <stdlib.h>
#include "my_adc.h"
void ADC_SETUP(char* str, int adc){//e.g. PA0
	if(str[1]=='A'){	//when GPIO A is used
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;		//GPIO clock enable
		GPIOA->MODER|=(3u<<(2*atoi(&str[2])));//ADC input pin is analogue mode
	}
	
	if(str[1]=='B'){												//when GPIO B is used
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN;		//GPIO clock enable
		GPIOB->MODER|=(3u<<(2*atoi(&str[2])));//ADC input pin is analogue mode
	}
	
	if(str[1]=='C'){												//when GPIO C is used
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOCEN;		//GPIO clock enable
		GPIOC->MODER|=(3u<<(2*atoi(&str[2])));//ADC input pin is analogue mode
	}
	if(str[1]=='D'){												//when GPIO C is used
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIODEN;		//GPIO clock enable
		GPIOD->MODER|=(3u<<(2*atoi(&str[2])));//ADC input pin is analogue mode
	}
	if(str[1]=='E'){												//when GPIO C is used
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOEEN;		//GPIO clock enable
		GPIOE->MODER|=(3u<<(2*atoi(&str[2])));//ADC input pin is analogue mode
	}
	if(str[1]=='F'){												//when GPIO C is used
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOFEN;		//GPIO clock enable
		GPIOF->MODER|=(3u<<(2*atoi(&str[2])));//ADC input pin is analogue mode
	}
	if(adc==1){														//if the ADC selected by user is 1
		RCC->APB2ENR|=RCC_APB2ENR_ADC1EN;		//ADC1 clock enable
		ADC1->SQR1&=~ADC_SQR1_L;						//set number of conversions per sequence to 1
		ADC1->SQR3&=~ADC_SQR3_SQ1;					//clear channel select bits
		ADC1->SQR3|=atoi(&str[2]);					//set channel
		ADC1->CR2|=ADC_CR2_ADON;						//enable ADC
	}
	if(adc==2){														//if the ADC selected by user is 2
		RCC->APB2ENR|=RCC_APB2ENR_ADC2EN;		//ADC1 clock enable
		ADC2->SQR1&=~ADC_SQR1_L;						//set number of conversions per sequence to 1
		ADC2->SQR3&=~ADC_SQR3_SQ1;					//clear channel select bits
		ADC2->SQR3|=atoi(&str[2]);					//set channel
		ADC2->CR2|=ADC_CR2_ADON;						//enable ADC
	}	
	if(adc==3){														//if the ADC selected by user is 3
		RCC->APB2ENR|=RCC_APB2ENR_ADC3EN;		//ADC1 clock enable
		ADC3->SQR1&=~ADC_SQR1_L;						//set number of conversions per sequence to 1
		ADC3->SQR3&=~ADC_SQR3_SQ1;					//clear channel select bits
		ADC3->SQR3|=atoi(&str[2]);					//set channel
		ADC3->CR2|=ADC_CR2_ADON;						//enable ADC
	}	
}
void ADCstartconv(int adc){
	if(adc==1){
		ADC1->CR2|=ADC_CR2_SWSTART;
	}
	if(adc==2){
		ADC2->CR2|=ADC_CR2_SWSTART;
	}
	if(adc==3){
		ADC3->CR2|=ADC_CR2_SWSTART;
	}
}
int ADCout(int adc){
	int out;
	if(adc==1){
		out=ADC1->DR;
	}
	if(adc==2){
		out=ADC2->DR;
	}
	if(adc==3){
		out=ADC3->DR;
	}
	return out;
}
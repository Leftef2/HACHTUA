#include "my_usart.h"
#include "my_functions.h"

void USART_setup(char* Pin1,char* Pin2){
	if(&Pin1[1]==&Pin2[1]){//checks if the pins work of the same GPIO
		if(Pin1[1]=='A'){
			RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;
			GPIOA->MODER&=~(3u<<(getNum(Pin1)*2))//sets the Pin to 00
			GPIOA->MODER|=(2u<<(getNum(Pin1)*2))//sets the Pin to 10
			GPIOA->MODER&=~(3u<<(getNum(Pin2)*2))
			GPIOA->MODER|=(2u<<(getNum(Pin2)*2))
			
		}
		else if(Pin1[1]=='B'){
			RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN;
			GPIOB->MODER&=~(3u<<(getNum(Pin1)*2))//sets the Pin to 00
			GPIOB->MODER|=(2u<<(getNum(Pin1)*2))//sets the Pin to 10
			GPIOB->MODER&=~(3u<<(getNum(Pin2)*2))
			GPIOB->MODER|=(2u<<(getNum(Pin2)*2))

		}
		else if(Pin1[1]=='C'){
			RCC->AHB1ENR|=RCC_AHB1ENR_GPIOCEN;
			GPIOC->MODER&=~(3u<<(getNum(Pin1)*2))//sets the Pin to 00
			GPIOC->MODER|=(2u<<(getNum(Pin1)*2))//sets the Pin to 10
			GPIOC->MODER&=~(3u<<(getNum(Pin2)*2))
			GPIOC->MODER|=(2u<<(getNum(Pin2)*2))

		}		
		else if(Pin1[1]=='D'){
			RCC->AHB1ENR|=RCC_AHB1ENR_GPIODEN;
			GPIOD->MODER&=~(3u<<(getNum(Pin1)*2))//sets the Pin to 00
			GPIOD->MODER|=(2u<<(getNum(Pin1)*2))//sets the Pin to 10
			GPIOD->MODER&=~(3u<<(getNum(Pin2)*2))
			GPIOD->MODER|=(2u<<(getNum(Pin2)*2))

		}				
		else if(Pin1[1]=='E'){
			RCC->AHB1ENR|=RCC_AHB1ENR_GPIOEEN;
			GPIOE->MODER&=~(3u<<(getNum(Pin1)*2))//sets the Pin to 00
			GPIOE->MODER|=(2u<<(getNum(Pin1)*2))//sets the Pin to 10
			GPIOE->MODER&=~(3u<<(getNum(Pin2)*2))
			GPIOE->MODER|=(2u<<(getNum(Pin2)*2))
		}			
		else if(Pin1[1]=='F'){
			RCC->AHB1ENR|=RCC_AHB1ENR_GPIOFEN;
			GPIOF->MODER&=~(3u<<(getNum(Pin1)*2))//sets the Pin to 00
			GPIOF->MODER|=(2u<<(getNum(Pin1)*2))//sets the Pin to 10
			GPIOF->MODER&=~(3u<<(getNum(Pin2)*2))
			GPIOF->MODER|=(2u<<(getNum(Pin2)*2))
		}
	}
}

		

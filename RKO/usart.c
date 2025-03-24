#include "usart.h"
#include "my_functions.h"
#include <stdlib.h>

void init_USART(int mod,char* Pin1,char* Pin2){
	if(Pin1[1]==Pin2[1]){//checks if the output and input use the same GPIO
		unsigned int p1,p2;	
		p1=getNum(Pin1)/8;											// used to select AFR[reg] for TX_pin ... pins 0-7 AFR[0] pins 8-15 AFR[1]
		p2=getNum(Pin2)>>3;											// same as above for RX_pin (uses shift to divide)
			
		if(Pin1[1]=='A'){
			RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;//enables port clock
			GPIOA->MODER&=~(3u<<(2*getNum(Pin1)));//sets 00 on both pins
			GPIOA->MODER&=~(3u<<(2*getNum(Pin2)));	
			
			GPIOA->MODER|=(2u<<(2*getNum(Pin1)));//sets pins to alternate function
			GPIOA->MODER|=(2u<<(2*getNum(Pin2)));
						
			//select alternate function
			GPIOA->AFR[p1]&=~(0x0f<<(4*(getNum(Pin1)-(p1*8))));    //clear pin function
			GPIOA->AFR[p1]|=(0x07<<(4*(getNum(Pin1)-(p1*8))));			// set usart as alternate function for TX_pin
			GPIOA->AFR[p2]&=~(0x0f<<(4*(getNum(Pin2)-(p2*8))));		// clear pin function
			GPIOA->AFR[p2]|=(0x07<<(4*(getNum(Pin2)-(p2*8))));			//set usart as alternate function for RX_pin

		}
		if(Pin1[1]=='B'){//repeat..
			RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN;
			GPIOB->MODER&=~(3u<<(2*getNum(Pin1)));
			GPIOB->MODER&=~(3u<<(2*getNum(Pin2)));	

			GPIOB->MODER|=(2u<<(2*getNum(Pin1)));
			GPIOB->MODER|=(2u<<(2*getNum(Pin2)));
			
			GPIOB->AFR[p1]&=~(0x0f<<(4*(getNum(Pin1)-(p1*8))));
			GPIOB->AFR[p1]|=(0x07<<(4*(getNum(Pin1)-(p1*8))));
			GPIOB->AFR[p2]&=~(0x0f<<(4*(getNum(Pin2)-(p2*8))));
			GPIOB->AFR[p2]|=(0x07<<(4*(getNum(Pin2)-(p2*8))));
		}
		if(Pin1[1]=='C'){
			RCC->AHB1ENR|=RCC_AHB1ENR_GPIOCEN;
			GPIOC->MODER&=~(3u<<(2*getNum(Pin1)));
			GPIOC->MODER&=~(3u<<(2*getNum(Pin2)));

			GPIOC->MODER|=(2u<<(2*getNum(Pin1)));
			GPIOC->MODER|=(2u<<(2*getNum(Pin2)));

			GPIOC->AFR[p1]&=~(0x0f<<(4*(getNum(Pin1)-(p1*8))));
			GPIOC->AFR[p1]|=(0x07<<(4*(getNum(Pin1)-(p1*8))));
			GPIOC->AFR[p2]&=~(0x0f<<(4*(getNum(Pin2)-(p2*8))));
			GPIOC->AFR[p2]|=(0x07<<(4*(getNum(Pin2)-(p2*8))));		
		}
		if(Pin1[1]=='D'){
			RCC->AHB1ENR|=RCC_AHB1ENR_GPIODEN;
			GPIOD->MODER&=~(3u<<(2*getNum(Pin1)));
			GPIOD->MODER&=~(3u<<(2*getNum(Pin2)));	

			GPIOD->MODER|=(2u<<(2*getNum(Pin1)));
			GPIOD->MODER|=(2u<<(2*getNum(Pin2)));
			
			GPIOD->AFR[p1]&=~(0x0f<<(4*(getNum(Pin1)-(p1*8))));
			GPIOD->AFR[p1]|=(0x07<<(4*(getNum(Pin1)-(p1*8))));
			GPIOD->AFR[p2]&=~(0x0f<<(4*(getNum(Pin2)-(p2*8))));
			GPIOD->AFR[p2]|=(0x07<<(4*(getNum(Pin2)-(p2*8))));
		}
		if(Pin1[1]=='E'){
			RCC->AHB1ENR|=RCC_AHB1ENR_GPIOEEN;
			GPIOE->MODER&=~(3u<<(2*getNum(Pin1)));
			GPIOE->MODER&=~(3u<<(2*getNum(Pin2)));	
			
			GPIOE->MODER|=(2u<<(2*getNum(Pin1)));
			GPIOE->MODER|=(2u<<(2*getNum(Pin2)));
			
			GPIOE->AFR[p1]&=~(0x0f<<(4*(getNum(Pin1)-(p1*8))));
			GPIOE->AFR[p1]|=(0x07<<(4*(getNum(Pin1)-(p1*8))));
			GPIOE->AFR[p2]&=~(0x0f<<(4*(getNum(Pin2)-(p2*8))));
			GPIOE->AFR[p2]|=(0x07<<(4*(getNum(Pin2)-(p2*8))));
		}
		if(Pin1[1]=='F'){
			RCC->AHB1ENR|=RCC_AHB1ENR_GPIOFEN;
			GPIOF->MODER&=~(3u<<(2*getNum(Pin1)));
			GPIOF->MODER&=~(3u<<(2*getNum(Pin2)));	
			
			GPIOF->MODER|=(2u<<(2*getNum(Pin1)));
			GPIOF->MODER|=(2u<<(2*getNum(Pin2)));
			
			GPIOF->AFR[p1]&=~(0x0f<<(4*(getNum(Pin1)-(p1*8))));
			GPIOF->AFR[p1]|=(0x07<<(4*(getNum(Pin1)-(p1*8))));
			GPIOF->AFR[p2]&=~(0x0f<<(4*(getNum(Pin2)-(p2*8))));
			GPIOF->AFR[p2]|=(0x07<<(4*(getNum(Pin2)-(p2*8))));
		}

	RCC->APB1ENR|=RCC_APB1ENR_USART3EN;			//usart clock enable
		if(mod==1){			//USART CONFIG
			USART1->CR1|=	USART_CR1_TE;//transmit enable
			USART1->CR1|=	USART_CR1_RE;//receive enable
			USART1->CR1|=	USART_CR1_UE;//usart main enable bit
			
			USART1->BRR=SystemCoreClock/(9600);		//set baud rate
																									//this is not an accurate way to set the baudrate
																									//and only works for 16Mhz system clock.
		}
		if(mod==2){			//USART CONFIG
			USART2->CR1|=	USART_CR1_TE;//transmit enable
			USART2->CR1|=	USART_CR1_RE;//receive enable
			USART2->CR1|=	USART_CR1_UE;//usart main enable bit
			
			USART2->BRR=SystemCoreClock/(9600);		//set baud rate (idk how this works so i stole it)
																									//this is not an accurate way to set the baudrate
																									//and only works for 16Mhz system clock.
		}
		if(mod==3){			//USART CONFIG
			USART3->CR1|=	USART_CR1_TE;//transmit enable
			USART3->CR1|=	USART_CR1_RE;//receive enable
			USART3->CR1|=	USART_CR1_UE;//usart main enable bit
			
			USART3->BRR=SystemCoreClock/(9600);		//set baud rate (idk how this works so i stole it)
																									//this is not an accurate way to set the baudrate
																									//and only works for 16Mhz system clock.
		}
		if(mod==4){			//USART CONFIG
			UART4->CR1|=	USART_CR1_TE;//transmit enable
			UART4->CR1|=	USART_CR1_RE;//receive enable
			UART4->CR1|=	USART_CR1_UE;//usart main enable bit
			
			UART4->BRR=SystemCoreClock/(9600);		//set baud rate (idk how this works so i stole it)
																									//this is not an accurate way to set the baudrate
																									//and only works for 16Mhz system clock.
		}
		if(mod==5){			//USART CONFIG
			UART5->CR1|=	USART_CR1_TE;//transmit enable
			UART5->CR1|=	USART_CR1_RE;//receive enable
			UART5->CR1|=	USART_CR1_UE;//usart main enable bit
			
			UART5->BRR=SystemCoreClock/(9600);		//set baud rate (idk how this works so i stole it)
																									//this is not an accurate way to set the baudrate
																									//and only works for 16Mhz system clock.
		}
		if(mod==7){			//USART CONFIG
			UART7->CR1|=	USART_CR1_TE;//transmit enable
			UART7->CR1|=	USART_CR1_RE;//receive enable
			UART7->CR1|=	USART_CR1_UE;//usart main enable bit
			
			UART7->BRR=SystemCoreClock/(9600);		//set baud rate (idk how this works so i stole it)
																									//this is not an accurate way to set the baudrate
																									//and only works for 16Mhz system clock.
		}
	}
}

void send_usart(int mod,unsigned char d)
{
	if(mod==1){
	    while(!(USART1->SR & USART_SR_TC));
	    USART1->DR=d;												//write byte to usart data register
	}
	else if(mod==2){
	    while(!(USART2->SR & USART_SR_TC));
	    USART2->DR=d;			//write byte to usart data register
	}
	else if(mod==3){
	    while(!(USART3->SR & USART_SR_TC));
	    USART3->DR=d;			//write byte to usart data register
	}
	else if(mod==4){
	    while(!(UART4->SR & USART_SR_TC));
	    UART4->DR=d;			//write byte to usart data register
	}
	else if(mod==5){
	    while(!(UART5->SR & USART_SR_TC));
	    UART5->DR=d;			//write byte to usart data register
	}
	else if(mod==7){
	    while(!(UART7->SR & USART_SR_TC));
	    UART7->DR=d;			//write byte to usart data register
	}
}
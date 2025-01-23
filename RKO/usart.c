#include "usart.h"
#include "my_functions.h"

int init_USART(int mod,char* Pin1,char* Pin2){
	if(Pin1[1]==Pin2[2]){//checks if the output and input use the same GPIO
		unsigned int p1,p2;		
		if(Pin1[1]=='A'){
			RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;//enables port clock
			GPIOA->MODER&=~(3u<<(2*getNum(Pin1)));//sets 00 on both pins
			GPIOA->MODER&=~(3u<<(2*getNum(Pin2)));	
			
			GPIOA->MODER|=(2u<<(2*getNum(Pin1)));//sets pins to alternate function
			GPIOA->MODER|=(2u<<(2*getNum(Pin2)));
			
			p1=getNum(Pin1)/8;											// used to select AFR[reg] for TX_pin ... pins 0-7 AFR[0] pins 8-15 AFR[1]
			p2=getNum(Pin2)>>3;											// same as above for RX_pin (uses shift to divide)
			
					// ALTERNATE FUNCTION SELECT BITS
			GPIOA->AFR[p1]&=~(0x0f<<(4*(getNum(Pin1)-(p1*8))));    //clear pin function
			GPIOA->AFR[p1]|=(0x07<<(4*(getNum(Pin1)-(p1*8))));			// set usart as alternate function for TX_pin
			GPIOA->AFR[p2]&=~(0x0f<<(4*(getNum(Pin2)-(p2*8))));		// clear pin function
			GPIOA->AFR[p2]|=(0x07<<(4*(getNum(Pin2)-(p2*8))));			//set usart as alternate function for RX_pin

		}
		if(Pin1[1]=='B'){
			return getNum(Pin2);
			RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN;//enables port clock
			GPIOB->MODER&=~(3u<<(2*getNum(Pin1)));//sets 00 on both pins
			GPIOB->MODER&=~(3u<<(2*getNum(Pin2)));	

			GPIOB->MODER|=(2u<<(2*getNum(Pin1)));//sets pins to alternate function
			GPIOB->MODER|=(2u<<(2*getNum(Pin2)));
			
					// ALTERNATE FUNCTION SELECT BITS
			GPIOB->AFR[p1]&=~(0x0f<<(4*(getNum(Pin1)-(p1*8))));    //clear pin function
			GPIOB->AFR[p1]|=(0x07<<(4*(getNum(Pin1)-(p1*8))));			// set usart as alternate function for TX_pin
			GPIOB->AFR[p2]&=~(0x0f<<(4*(getNum(Pin2)-(p2*8))));		// clear pin function
			GPIOB->AFR[p2]|=(0x07<<(4*(getNum(Pin2)-(p2*8))));			//set usart as alternate function for RX_pin
		}
		if(Pin1[1]=='C'){
			RCC->AHB1ENR|=RCC_AHB1ENR_GPIOCEN;//enables port clock
			GPIOC->MODER&=~(3u<<(2*getNum(Pin1)));//sets 00 on both pins
			GPIOC->MODER&=~(3u<<(2*getNum(Pin2)));

			GPIOC->MODER|=(2u<<(2*getNum(Pin1)));//sets pins to alternate function
			GPIOC->MODER|=(2u<<(2*getNum(Pin2)));

					// ALTERNATE FUNCTION SELECT BITS
			GPIOC->AFR[p1]&=~(0x0f<<(4*(getNum(Pin1)-(p1*8))));    //clear pin function
			GPIOC->AFR[p1]|=(0x07<<(4*(getNum(Pin1)-(p1*8))));			// set usart as alternate function for TX_pin
			GPIOC->AFR[p2]&=~(0x0f<<(4*(getNum(Pin2)-(p2*8))));		// clear pin function
			GPIOC->AFR[p2]|=(0x07<<(4*(getNum(Pin2)-(p2*8))));			//set usart as alternate function for RX_pin			
		}
		if(Pin1[1]=='D'){
			RCC->AHB1ENR|=RCC_AHB1ENR_GPIODEN;//enables port clock
			GPIOD->MODER&=~(3u<<(2*getNum(Pin1)));//sets 00 on both pins
			GPIOD->MODER&=~(3u<<(2*getNum(Pin2)));	
			
			GPIOD->MODER|=(2u<<(2*getNum(Pin1)));//sets pins to alternate function
			GPIOD->MODER|=(2u<<(2*getNum(Pin2)));
			
					// ALTERNATE FUNCTION SELECT BITS
			GPIOD->AFR[p1]&=~(0x0f<<(4*(getNum(Pin1)-(p1*8))));    //clear pin function
			GPIOD->AFR[p1]|=(0x07<<(4*(getNum(Pin1)-(p1*8))));			// set usart as alternate function for TX_pin
			GPIOD->AFR[p2]&=~(0x0f<<(4*(getNum(Pin2)-(p2*8))));		// clear pin function
			GPIOD->AFR[p2]|=(0x07<<(4*(getNum(Pin2)-(p2*8))));			//set usart as alternate function for RX_pin			
		}
		if(Pin1[1]=='E'){
			RCC->AHB1ENR|=RCC_AHB1ENR_GPIOEEN;//enables port clock
			GPIOE->MODER&=~(3u<<(2*getNum(Pin1)));//sets 00 on both pins
			GPIOE->MODER&=~(3u<<(2*getNum(Pin2)));	
			
			GPIOE->MODER|=(2u<<(2*getNum(Pin1)));//sets pins to alternate function
			GPIOE->MODER|=(2u<<(2*getNum(Pin2)));
			
					// ALTERNATE FUNCTION SELECT BITS
			GPIOE->AFR[p1]&=~(0x0f<<(4*(getNum(Pin1)-(p1*8))));    //clear pin function
			GPIOE->AFR[p1]|=(0x07<<(4*(getNum(Pin1)-(p1*8))));			// set usart as alternate function for TX_pin
			GPIOE->AFR[p2]&=~(0x0f<<(4*(getNum(Pin2)-(p2*8))));		// clear pin function
			GPIOE->AFR[p2]|=(0x07<<(4*(getNum(Pin2)-(p2*8))));			//set usart as alternate function for RX_pin			
		}
		if(Pin1[1]=='F'){
			RCC->AHB1ENR|=RCC_AHB1ENR_GPIOFEN;//enables port clock
			GPIOF->MODER&=~(3u<<(2*getNum(Pin1)));//sets 00 on both pins
			GPIOF->MODER&=~(3u<<(2*getNum(Pin2)));	
			
			GPIOF->MODER|=(2u<<(2*getNum(Pin1)));//sets pins to alternate function
			GPIOF->MODER|=(2u<<(2*getNum(Pin2)));
			
					// ALTERNATE FUNCTION SELECT BITS
			GPIOF->AFR[p1]&=~(0x0f<<(4*(getNum(Pin1)-(p1*8))));    //clear pin function
			GPIOF->AFR[p1]|=(0x07<<(4*(getNum(Pin1)-(p1*8))));			// set usart as alternate function for TX_pin
			GPIOF->AFR[p2]&=~(0x0f<<(4*(getNum(Pin2)-(p2*8))));		// clear pin function
			GPIOF->AFR[p2]|=(0x07<<(4*(getNum(Pin2)-(p2*8))));			//set usart as alternate function for RX_pin			
		}

	RCC->APB1ENR|=RCC_APB1ENR_USART3EN;			//usart clock enable
		if(mod==2){			//USART CONFIG
			USART2->CR1|=	USART_CR1_TE;//transmit enable
			USART2->CR1|=	USART_CR1_RE;//receive enable
			USART2->CR1|=	USART_CR1_UE;//usart main enable bit
			
			USART2->BRR=SystemCoreClock/(9600);		//set baud rate
																									//this is not an accurate way to set the baudrate
																									//and only works for 16Mhz system clock.
		}
		if(mod==3){			//USART CONFIG
			USART3->CR1|=	USART_CR1_TE;//transmit enable
			USART3->CR1|=	USART_CR1_RE;//receive enable
			USART3->CR1|=	USART_CR1_UE;//usart main enable bit
			
			USART3->BRR=SystemCoreClock/(9600);		//set baud rate
																									//this is not an accurate way to set the baudrate
																									//and only works for 16Mhz system clock.
		}
		

	}																									
}

void send_usart(int mod,unsigned char d)
{
	if(mod==2){
	    while(!(USART2->SR & USART_SR_TC));
	    USART2->DR=d;												//write byte to usart data register
	}
	else if(mod==3){
	    while(!(USART3->SR & USART_SR_TC));
	    USART3->DR=d;			//write byte to usart data register
	}
}
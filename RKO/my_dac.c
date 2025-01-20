#include <stm32f429xx.h>
#include <stdlib.h>
#include "my_dac.h"
void DAC_SETUP(char* str, int dac){					//e.g. PA4
	
	if(str[1]=='A'){													//when GPIO A is used	
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;			//DAC port clock enable
		DAC_port->MODER|=(3u<<(2*DAC_pin));			//DAC output pin set as anaglogue
		
		RCC->APB1ENR|=RCC_APB1ENR_DACEN;				//DAC clock enable
		DAC->CR|=DAC_CR_EN2;										//DAC 2 enabled
	}
	
	if(str[1]=='B'){													//when GPIO B is used	
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;			//DAC port clock enable
		DAC_port->MODER|=(3u<<(2*DAC_pin));			//DAC output pin set as anaglogue
		
		RCC->APB1ENR|=RCC_APB1ENR_DACEN;				//DAC clock enable
		DAC->CR|=DAC_CR_EN2;										//DAC 2 enabled
	}
	
	if(str[1]=='C'){													//when GPIO C is used	
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;			//DAC port clock enable
		DAC_port->MODER|=(3u<<(2*DAC_pin));			//DAC output pin set as anaglogue
		
		RCC->APB1ENR|=RCC_APB1ENR_DACEN;				//DAC clock enable
		DAC->CR|=DAC_CR_EN2;										//DAC 2 enabled
	}
	
	if(str[1]=='D'){													//when GPIO D is used	
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;			//DAC port clock enable
		DAC_port->MODER|=(3u<<(2*DAC_pin));			//DAC output pin set as anaglogue
		
		RCC->APB1ENR|=RCC_APB1ENR_DACEN;				//DAC clock enable
		DAC->CR|=DAC_CR_EN2;										//DAC 2 enabled
	}
	
	if(str[1]=='E'){													//when GPIO E is used	
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;			//DAC port clock enable
		DAC_port->MODER|=(3u<<(2*DAC_pin));			//DAC output pin set as anaglogue
		
		RCC->APB1ENR|=RCC_APB1ENR_DACEN;				//DAC clock enable
		DAC->CR|=DAC_CR_EN2;										//DAC 2 enabled
	}
	
	if(str[1]=='F'){													//when GPIO F is used	
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;			//DAC port clock enable
		DAC_port->MODER|=(3u<<(2*DAC_pin));			//DAC output pin set as anaglogue
		
		RCC->APB1ENR|=RCC_APB1ENR_DACEN;				//DAC clock enable
		DAC->CR|=DAC_CR_EN2;										//DAC 2 enabled
	}
	
	if(str[1]=='1'){													//when GPIO 1 is used	
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;			//DAC port clock enable
		DAC_port->MODER|=(3u<<(2*DAC_pin));			//DAC output pin set as anaglogue
		
		RCC->APB1ENR|=RCC_APB1ENR_DACEN;				//DAC clock enable
		DAC->CR|=DAC_CR_EN2;										//DAC 2 enabled
	}
	
	if(str[1]=='2'){													//when GPIO 2 is used	
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;			//DAC port clock enable
		DAC_port->MODER|=(3u<<(2*DAC_pin));			//DAC output pin set as anaglogue
		
		RCC->APB1ENR|=RCC_APB1ENR_DACEN;				//DAC clock enable
		DAC->CR|=DAC_CR_EN2;										//DAC 2 enabled
	}
	
	if(str[1]=='3'){													//when GPIO 3 is used	
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;			//DAC port clock enable
		DAC_port->MODER|=(3u<<(2*DAC_pin));			//DAC output pin set as anaglogue
		
		RCC->APB1ENR|=RCC_APB1ENR_DACEN;				//DAC clock enable
		DAC->CR|=DAC_CR_EN2;										//DAC 2 enabled
	}
	
	void output_dac(unsigned short d)
{
	DAC->DHR12R2=d;			//write data byte to DAC 2 output register
}

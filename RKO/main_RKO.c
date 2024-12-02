#include <stm32f429xx.h>		//INCLUDE THE HEADER FILE FOR THIS MCU FAMILY
#include <core_cm4.h>
#include "lcd.h"
#include "stdio.h"
#include <string.h>
#include <stdlib.h>

void ADC_SETUP(char* str, int adc){//e.g. PA0

	if(strcmp(&str[2],"A")==0){							//when GPIO A is used
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;		//GPIO clock enable
		GPIOA->MODER|=(3u<<(2*atoi(&str[2])));//ADC input pin is analogue mode
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
void LED_INIT (void)
{
	//ENABLE PORT(S)
	//RCC->AHB1ENR |= 0x02;						//use label defined in stm32f4.h instead of hex value: easier to read and change
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;	//ONLY GPIO B clock enable
	
	//CONFIGURE PORT:GPIOB  PIN:0 TO OUTPUT for LED1
	GPIOB->MODER |= 0x01;						//ONLY set  GPIOB0
	// the above assumes that bit 1 is to zero
	GPIOB->MODER &= ~0x02;					//ONLY clear GPIOB1
	
	//CONFIGURE PORT:GPIOB  PIN:7 TO OUTPUT for LED2
	GPIOB->MODER |= (1<<14);						//ONLY set  GPIOB7
	
	//CONFIGURE PORT:GPIOB  PIN:14 TO OUTPUT for LED3
	GPIOB->MODER |= (1<<28);						//ONLY set  GPIOB14


}	
void LED1_ON (void)
{
			GPIOB->ODR |= 1;							//ONLY TURN LED ON
}

void LED1_OFF (void)
{
			GPIOB->ODR &= ~1;							//ONLY TURN LED ON
}
void LED2_ON (void)
{
			GPIOB->ODR |= (1<<7);							//ONLY TURN LED ON
}

void LED2_OFF (void)
{
			GPIOB->ODR &= ~(1<<7);							//ONLY TURN LED ON
}
void LED3_ON (void)
{
			GPIOB->ODR |= (1<<14);							//ONLY TURN LED ON
}

void LED3_OFF (void)
{
			GPIOB->ODR &= ~(1<<14);							//ONLY TURN LED ON
}
int main(void){
	char* str="PA0";
	int out;
  int A;
	initLCD();
	cmdLCD(LCD_LINE1);
	ADC_SETUP("PA0",1);
	LED_INIT();
  char Sout[20];

	while(1){


		clr_LCD_RS();
		for(A=0;A<sizeof(Sout);A++){
			WaitLcdBusy();
			sprintf(Sout,strcat("output is= %5.i",&str[1]));
			putLCD(Sout[A]);
		};
		ADC1->CR2|=ADC_CR2_SWSTART;				//start ADC conversion
		while((ADC1->SR&ADC_SR_EOC)==0){};
		out=ADC1->DR;
		if(out<1366){
			LED1_ON();
		}
		else{
			LED1_OFF();
		}
		if(1366<out&out<2732){
			LED2_ON();
		}
		else{
			LED2_OFF();
		}
		if(out>2732){
			LED3_ON();
		}
		else{
			LED3_OFF();
		}		

	}
}

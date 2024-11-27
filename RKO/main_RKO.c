#include <stm32f429xx.h>		//INCLUDE THE HEADER FILE FOR THIS MCU FAMILY
#include <core_cm4.h>
#include "lcd.h"
#include "stdio.h"
void delay (void)
{	
	volatile unsigned int i;		//create variable
	for (i=0; i<1000000; i++);	//WAIT count to 1 million 
}
void ADC_SETUP(void){
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;	//GPIOC clock enable
	GPIOA->MODER|=(3u<<(2*0));	//ADC input pin is analogue mode
	RCC->APB2ENR|=RCC_APB2ENR_ADC1EN;		//ADC clock enable
	ADC1->SQR1&=~ADC_SQR1_L;						//set number of conversions per sequence to 1
	ADC1->SQR3&=~ADC_SQR3_SQ1;					//clear channel select bits
	ADC1->SQR3|=0;						//set channel
	ADC1->CR2|=ADC_CR2_ADON;						//enable ADC
	

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
	
	int out;
  int A;
	initLCD();
	cmdLCD(LCD_LINE1);
	ADC_SETUP();
	LED_INIT();
  char Sout[20];

	while(1){
		clr_LCD_RS();
		for(A=0;A<sizeof(Sout);A++){
			WaitLcdBusy();
			sprintf(Sout,"output is= %5.i",out);
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

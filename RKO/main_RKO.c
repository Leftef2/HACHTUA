#include <stm32f429xx.h>		//INCLUDE THE HEADER FILE FOR THIS MCU FAMILY
#include <core_cm4.h>
#include "lcd.h"
#include "stdio.h"
#include <string.h>
#include <stdlib.h>
#include "my_adc.h"


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
  int A;
	initLCD();
	ADC_SETUP("PA7",1);
	LED_INIT();
	clr_LCD_RS();
	char Sout[20];
	while(1){
		ADCstartconv(1);				//start ADC conversion
		sprintf(Sout,"output is= %5.i\n",ADCout(1));
		cmdLCD(LCD_LINE1);
		for(A=0;A<sizeof(Sout);A++){
			WaitLcdBusy();
			putLCD(Sout[A]);
		};
		sprintf(Sout,"                  \n");
		cmdLCD(LCD_LINE2);
		for(A=0;A<sizeof(Sout);A++){
			WaitLcdBusy();
			putLCD(Sout[A]);
		};

		if(ADCout(1)<1366){
			LED1_ON();
		}
		else{
			LED1_OFF();
		}
		if(1366<ADCout(1)&ADCout(1)<2732){
			LED2_ON();
		}
		else{
			LED2_OFF();
		}
		if(ADCout(1)>2732){
			LED3_ON();
		}
		else{
			LED3_OFF();
		}		

	}
}

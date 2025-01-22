#include <stm32f429xx.h>		//INCLUDE THE HEADER FILE FOR THIS MCU FAMILY
#include <core_cm4.h>
#include "lcd.h"
#include "stdio.h"
#include <string.h>
#include <stdlib.h>
#include "my_adc.h"
#include "my_led.h"
#include "my_functions.h"
#include "my_usart.h"


int main(void){
	int A;
	initLCD();
	ADC_SETUP("PA0",1);//sets up PA0 and selects which ADC to use
	LED_SETUP("PB0");
	LED_SETUP("PB7");
	LED_SETUP("PB14");
	clr_LCD_RS();
	USART_setup("PB8","PB9");
	char Sout[20];
	while(1){
		ADCstartconv(1);				//start ADC conversion
		sprintf(Sout,"output is= %5.i\n",ADCout(1));
		char Test[4]="PB12";
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
			LED_ON("PB0");
		}
		else{
			LED_OFF("PB0");
		}
		if(1366<ADCout(1)&ADCout(1)<2732){
			LED_ON("PB7");
		}
		else{
			LED_OFF("PB7");
		}
		if(ADCout(1)>2732){
			LED_ON("PB14");
		}
		else{
			LED_OFF("PB14");
		}	
		

	}
}

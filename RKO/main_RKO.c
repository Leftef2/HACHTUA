#include <stm32f429xx.h>		//INCLUDE THE HEADER FILE FOR THIS MCU FAMILY
#include <core_cm4.h>
#include "lcd.h"
#include "stdio.h"
#include <string.h>
#include <stdlib.h>
#include "my_adc.h"
#include "my_led.h"
#include "my_functions.h"
#include "usart.h"
#include "my_switch.h"
#include "my_buzzer.h"

int main(void){
	int A;
	initLCD();
	ADC_SETUP("PA0",1);//sets up PA0 and selects which ADC to use
	LED_SETUP("PB0");
	LED_SETUP("PB7");
	LED_SETUP("PB14");
	clr_LCD_RS();
	init_USART(3,"PD8","PD9");
	createSwitch("PC13");

	
	char Sout[20];
	while(1){
		send_usart(3,'A');
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

		
		int Z;
		while(Switch("PC13")){
				Z=!Z;
				if(Z==1){
					BUZZER_ON("PB13");
				}
				else{
					BUZZER_OFF("PB13");
				}
			}
		if(!Switch("PC13")){
			BUZZER_OFF("PB13");
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

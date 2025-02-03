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
#include "timers.h"
#include "my_dac.h"
void Shortbuzz(void){
	int a=0;
	int buz=0;
	int time=0;
	while(a==0){
		TIM2_IRQHandler();
		buz++;
		time++;
		if(buz>400){
			buz=0;
		}
		if(buz>200){
			LED_ON("PB13");		//Turn on LED
		}
		else{
			LED_OFF("PB13"); //Turn off LED
		}
		if(time>79000){	// Time Interval (104bpm)
			break;
		}
	}	
}
			
int main(void){
	int A;
	int K;
	int debounce=0;
	initLCD();
	ADC_SETUP("PA0",1);		//sets up PA0 and selects which ADC to use
	LED_SETUP("PB0");			// Set up LED
	LED_SETUP("PB7");			// Set up LED
	LED_SETUP("PB14");		// Set up LED
	LED_SETUP("PB13");		// Set up LED
	clr_LCD_RS();					// Clear LCD
	init_USART(3,"PD8","PD9");
	createSwitch("PG0");// Set up switch A
	createSwitch("PG1");// Set up switch B
	createSwitch("PG2");// Set up switch C
	createSwitch("PG3");	//Set up switch D
	createSwitch("PC13"); //Set up Blue Button
	timer_init();         //set up timer
	Init_DAC2();					// Set up DAC
	
//Ramp_Output();
//Square_Output();
	DC_level();
//	Complex_Output();
	
		char Sout[20];
	while(1){
			send_usart(3,'A');
		ADCstartconv(1);				//start ADC conversion
		sprintf(Sout,"output is= %5.i\n",ADCout(1));
		sprintf(Sout,"output is= %5.i\n",ADCout(1));
		
		//LCD line 1
	cmdLCD(LCD_LINE1);	
		for(A=0;A<sizeof(Sout);A++){
			WaitLcdBusy();
			putLCD(Sout[A]);
		};
		sprintf(Sout,"                  \n");
			
//LCD line 2
		int B;
	char T[]="Blood O2:";
	cmdLCD(LCD_LINE2);
	for(B=0;B <sizeof(T)-1;B++){
		WaitLcdBusy();
		putLCD(T[B]);
	}
	
		TIM2_IRQHandler();
		A++;
		ADCstartconv(1);
		if(Switch("PC13")==1){
			Shortbuzz();
		}

		if(Switch("PC13")==1){	// Blue Button
			Delay_ms(40);					// Debounce
			if(ADCout(1)<1366){		// ADC Condition
				
				LED_ON("PB0");			//Turn on LED
			}
			else{
				LED_OFF("PB0");		//Turn off LED
			}
			if(1366<ADCout(1)&ADCout(1)<2732){
				LED_ON("PB7");	//Turn on LED
			}
			else{
				LED_OFF("PB7");	//Turn off LED
			}			
			if(Switch("PC13")==1){
				LED_ON("PB14");		//Turn on LED
			}
			else{
				LED_OFF("PB14"); //Turn off LED
			}
//			if(Switch("PG0")&&debounce==0){
//				debounce=A;
//			}
//			if((A+200000)>debounce){
//					LED_ON("PB0");
//				debounce=0;
//			}
				
				
		}
	}
	
}

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

int main(void){
	int A;
	int K;
	initLCD();
	ADC_SETUP("PA0",1);//sets up PA0 and selects which ADC to use
	LED_SETUP("PB0");
	LED_SETUP("PB7");
	LED_SETUP("PB14");
	LED_SETUP("PB13");
	clr_LCD_RS();
	init_USART(3,"PD8","PD9");

	timer_init();
	
	char Sout[20];
	while(1){
		timer9KHzhold();
		//send_usart(3,'A');


		K++;
		if(K>960){
			K=0;
		}
		if(K<460){
			LED_ON("PB0");
		}
		else{
			LED_OFF("PB0");
		}
			if(ADCout(1)<1366){
		//		LED_ON("PB0");
		}
			else{
		//		LED_OFF("PB0");
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
			timer_init();
		}
}

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
//	createSwitch("PG0");
	timer_init();
	
	char Sout[20];
	while(1){
		TIM2_IRQHandler();
//		ADCstartconv(1);
		K=!K;
		if(K){
			LED_ON("PB13");
			LED_ON("PB0");
		}
		else{
			LED_OFF("PB13");
//			LED_OFF("PB0");
		}
//		if(Switch("PG0")==1){
//			if(1366>ADCout(1)){
				//LED_ON("PB0");
	//		}
//			else{
				//LED_OFF("PB0");
//			}
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

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
			LED_ON("PB13");
		}
		else{
			LED_OFF("PB13");
		}
		if(time>200000){
			break;
		}
	}	
}
			
int main(void){
	int mode=2;
	int A;
	int K;
	int FlashLedCount;
	initLCD();
	ADC_SETUP("PA0",1);//sets up PA0 and selects which ADC to use
	LED_SETUP("PB0");
	LED_SETUP("PB7");
	LED_SETUP("PB14");
	LED_SETUP("PB13");
	clr_LCD_RS();
	init_USART(3,"PD8","PD9");
	createSwitch("PG0");
	createSwitch("PG3");
	timer_init();
	
	char Sout[20];
	while(1){
		TIM2_IRQHandler();
		ADCstartconv(1);
		if(FlashLedCount>(100000*mode)){
			FlashLedCount=0;
		}
		else{
			FlashLedCount++;
		}
		if(FlashLedCount<100000&&FlashLedCount!=0){
			LED_ON("PB14");
		}
		else{
			LED_OFF("PB14");
		}

		if(Switch("PG3")==1){
			Shortbuzz();
		}
	}
}

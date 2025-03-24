#include "my_functions.h"
#include <stdlib.h>
#include "lcd.h"
#include "my_adc.h"
#include "my_switch.h"
#include "timers.h"
#include "my_dac.h"
#include "my_led.h"
#include "usart.h"

_ARMABI size_t strlen(const char * /*s*/) __attribute__((__nonnull__(1)));//i stole this lol (makes strlen() work)

void send_Line1(char* str){
	cmdLCD(LCD_LINE1);
	for(int A=0;A<16;A++){
		if(A<strlen(str)){//for each character of str, send it to the display (putLCD takes care of refreshing ports)
			putLCD(str[A]);
		}
		else{
			putLCD(' ');
		}
	}
}

void send_Line2(char* str){
	cmdLCD(LCD_LINE2);
	for(int A=0;A<16;A++){//same as above but for line 2
		if(A<strlen(str)){
			putLCD(str[A]);
		}
		else{
			putLCD(' ');
		}
	}
}


int getNum(char* str){//creates a function that returns the pin number inputted from the string
	if(sizeof(str)==5){
		return (atoi(&str[2])*10)+atoi(&str[3]);
	}
	else if(atoi(&str[2])==0){
		return 0;
	}
	else{
		return atoi(&str[2]);
	}
}

void debounce(void)         //blocking delay for startup splashscreen
{
	for(int i=0; i<100000000; i++){__NOP();}
}

void menu_debounce(void)         //blocking delay for LCD
{
	for(int i=0; i<100000; i++){__NOP();}
}


void Shortbuzz(void){
	int buz=0;
	int time=0;
	while(1){
		buz++;//if this counter goes above 400, reset the counter (FOR BUZZ)
		time++;//if this counter goes above 200000, reset the counter (FOR SPACE IN BUZZ)
		if(buz>400){
			buz=0;
		}
		if(buz>200){
			LED_ON("PB13");
		}
		else{//basically switch at half the frequency set by buz++ (i can't be bothered to work it out)
			LED_OFF("PB13");
		}
		if(time>100000){
			break;
		}
	}	
}

void init(void){
	createSwitch("PG0");
	createSwitch("PG1");
	createSwitch("PG2");
	createSwitch("PG3");
	//init_USART();
	LED_SETUP("PB13");
	init_DAC();
	ADC_SETUP("PA4",1);
	initLCD();
	timer_init();
	send_Line1("Loading system..");
	debounce();
}
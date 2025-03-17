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
//void menu_debounce_function(void)         //blocking delay for LCD, argument is approximate number of micro-seconds to delay
//{
//	unsigned char i;
//	int Time=5000;
//	while(Time--)
//	{
//		for(i=0; i<SystemCoreClock/4000000; i++){__NOP();}
//	}
//}
void send_Line1(char* str){
	cmdLCD(LCD_LINE1);
	for(int A=0;A<16;A++){
		if(A<strlen(str)){
			putLCD(str[A]);
		}
		else{
			putLCD(' ');
		}
	}
}
void send_Line2(char* str){
	cmdLCD(LCD_LINE2);
	for(int A=0;A<16;A++){
		if(A<strlen(str)){
			putLCD(str[A]);
		}
		else{
			putLCD(' ');
		}
	}
}

int Choice=0;
void menu(int ScrollLocal){
	//send_Line1("      bpm       ");  Choice=1
	//send_Line1("       o2       ");  Choice=2
	//send_Line1("     options    ");  Choice=3
	//send_Line1("   CPR assist   ");  Choice=4
	//send_Line1("    credits     ");  Choice=5
	if(ScrollLocal==0){
		send_Line1("    --bpm--     ");
		send_Line2("       o2       ");
		Choice=1;
	}
	if(ScrollLocal==1){
		send_Line1("      bpm       ");
		send_Line2("     --o2--     ");
		Choice=2;
	}	
	if(ScrollLocal==2){
		send_Line1("     --o2--     ");
		send_Line2("     options    ");
		Choice=2;
	}	
	if(ScrollLocal==3){
		send_Line1("       o2       ");
		send_Line2("   --options--  ");
		Choice=3;
	}		
	if(ScrollLocal==4){
		send_Line1("   --options--  ");
		send_Line2("   CPR assist   ");
		Choice=3;
	}		
	if(ScrollLocal==5){
		send_Line1("     options    ");
		send_Line2(" --CPR assist-- ");
		Choice=4;
	}	
	if(ScrollLocal==6){
		send_Line1(" --CPR assist-- ");
		send_Line2("     credits    ");
		Choice=4;
	}		
	if(ScrollLocal==7){
		send_Line1("   CPR assist   ");
		send_Line2("   --credits--  ");
		Choice=5;
	}		
	if(ScrollLocal==8){
		send_Line1("   --credits--  ");
		send_Line2("                ");
		Choice=5;
	}	
}
int RunningAverageStore[201];
int RunningAverage(int A){
	int Average=0;
	for(int I=0;I<200;I++){
		RunningAverageStore[I]=RunningAverageStore[I+1];
	}
	RunningAverageStore[200]=A;
	for(int I=0;I<200;I++){
		Average=Average+RunningAverageStore[I];
	}
	Average=Average/200;
		
	return Average;
}
int ActiveChoice=0;
int Scroll=0;
int BPM;
char temp[17];
int LED1=0;
int A=0;
int main(void){
	LED_SETUP("PF14");
	//LED_SETUP("PA5");
	initLCD();
	send_Line1("Loading system...");
	LED_SETUP("PB0");
	createSwitch("PG0");
	createSwitch("PG2");
	createSwitch("PG3");
	LED_SETUP("PB7");
	LED_SETUP("PB14");
	ADC_SETUP("PA4",1);
	timer_init();
	Init_DAC2();
	menu(Scroll);
	LED_ON("PF14");
	send_dac((1<<11));
	while(1){
		if(ActiveChoice==0){
			while(!Switch("PG0")&&!Switch("PG2")&&!Switch("PG3")){};
			menu_debounce_function();
				if(Switch("PG2")){
				Scroll=Scroll+1;
			}
			if(Switch("PG0")){
				Scroll=Scroll-1;
			}
			if(Scroll>=9){
				Scroll=0;
			}
			if(Scroll<0){
				Scroll=6;
			}
			if(Switch("PG3")){
				ActiveChoice=Choice;
			}
			menu(Scroll);
			while(Switch("PG0")||Switch("PG2")||Switch("PG3")){};
		}
		if(ActiveChoice==1){
			sprintf(temp,"BPM:%1.i|",A);
			send_Line1(temp);
			sprintf(temp,"Val:%1.i|",(int) round(ADCout(1)));
			send_Line2(temp);
		}
	}
}


int Counter=0;
int ClockEnable=0;
int FlipFlop=0;
void TIM2_IRQHandler(void)			//TIMER 2 INTERRUPT SERVICE ROUTINE -- 20Hz Loop --
{
	
	TIM2->SR&=~TIM_SR_UIF;				//clear interrupt flag in status register
	if(ActiveChoice==1){
		if(ClockEnable==1){
			Counter++;
		}
		A=RunningAverage(ADCout(1));		
		ADCstartconv(1);
		if(ADCout(1)>A){
			if(FlipFlop==0){
				BPM=Counter;
				Counter=0;
				ClockEnable=!ClockEnable;
				FlipFlop=1;
			}
		}
		else{
			FlipFlop=0;
		}
	}
}
	
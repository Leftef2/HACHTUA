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
void send_Line1(char* str){
	cmdLCD(LCD_LINE1);
	for(int A=0;16;A++){
		if(A<strlen(str)){
			putLCD(str[A]);
		}
		else{
			putLCD(' ');
		}
		if(A==16){
			break;
		}
	}
}
void send_Line2(char* str){
	cmdLCD(LCD_LINE2);
	for(int A=0;strlen(str);A++){
		putLCD(str[A]);
		if(strlen(str)-1==A){
			break;
		}
	}
}

int main(void){
	timer_init();
	initLCD();
	LED_SETUP("PD14");
	send_Line1("Loading system...");
	createSwitch("PG0");
	createSwitch("PG2");
	while(1){
		;
	}
}
int Counter;
int A=0;
int MenuPos=0;
int Wait=0;
int Selected=0;
void TIM2_IRQHandler(void)			//TIMER 2 INTERRUPT SERVICE ROUTINE -- 120 FPS Loop --
{
	TIM2->SR&=~TIM_SR_UIF;				//clear interrupt flag in status register
	Counter++;
	if(Wait==0){
		if(Switch("PG2")){
			if(Selected==0&&MenuPos==3){
				MenuPos=0;
				Selected=0;
			}
			else if(Selected<1){
				Selected=1;
			}
			else{
				MenuPos=MenuPos+1;
				Selected=0;
			}
			Wait=1;
		}
		if(Switch("PG0")){
			if(Selected==0&&MenuPos==0){
				MenuPos=3;
				Selected=0;
			}
			else if(Selected>0){
				Selected=0;
			}
			else{
				MenuPos=MenuPos-1;
				Selected=1;
			}
			Wait=1;
		}
	}
	if(!Switch("PG0")&&!Switch("PG2")){
		Wait=0;
	}
	//send_Line1("  bpm/o2 level  ");  MenuPos=0
	//send_Line1("   CPR assist   ");  MenuPos=1
	//send_Line1("     options    ");  MenuPos=2
	//send_Line1("     credits    ");  MenuPos=3
	if(Counter>240){
		if(MenuPos==0){
			if(Selected==0){
				send_Line1("--bpm/o2 level--");
				send_Line2("   CPR assist   ");	
			}		
			if(Selected==1){
				send_Line1("  bpm/o2 level  ");
				send_Line2(" --CPR assist-- ");	
			}
		}
		if(MenuPos==1){
			if(Selected==0){
				send_Line1(" --CPR assist-- ");
				send_Line2("     options    ");	
			}		
			if(Selected==1){
				send_Line1("   CPR assist   ");
				send_Line2("   --options--  ");	
			}
		}
		if(MenuPos==2){
			if(Selected==0){
				send_Line1("   --options--  ");
				send_Line2("     credits    ");	
			}		
			if(Selected==1){
				send_Line1("     options    ");
				send_Line2("   --credits--  ");	
			}
		}
		if(MenuPos==3){
			if(Selected==0){
				send_Line1("   --credits--  ");
				send_Line2("                ");	
			}		
		}		
	}
}
	
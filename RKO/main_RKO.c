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
//molex
//red 1
//black 2
//blue 3
//pink 4
//yellow 5
//green 6
void send_Line1(char* str){
	cmdLCD(LCD_LINE1);
	for(int A=0;strlen(str)-1;A++){
		putLCD(str[A]);
		if(A==16){
			break;
		}
	}
}
void send_Line2(char* str){
	cmdLCD(LCD_LINE2);
	for(int A=0;strlen(str)-1;A++){
		putLCD(str[A]);
		if(strlen(str)-1==A){
			break;
		}
	}
}
int Menu=0;
int main(void){
	timer_init();
	initLCD();
	LED_SETUP("PD14");
	LED_SETUP("PB13");
	send_Line1("Loading system...");
	createSwitch("PG0");
	createSwitch("PG2");
	createSwitch("PG3");
	ADC_SETUP("PA0",1);
	Menu=1;
	while(1){
		;
	}
}
int A=0;
int Counter;
int MenuPos=0;
int Wait=0;
int Selected=0;
int Mode=0;
int ActiveMode=0;
int BPMcount=0;
void TIM2_IRQHandler(void)			//TIMER 2 INTERRUPT SERVICE ROUTINE -- 120 FPS Loop --
{
	A=!A;
	if(A){
		set_LCD_E();
	}
	else{
		clr_LCD_E();
	}
		
	TIM2->SR&=~TIM_SR_UIF;				//clear interrupt flag in status register
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
		if(Menu){
			if(MenuPos==0){
				if(Selected==0){
					send_Line1("--bpm/o2 level--");
					Mode=1;
					send_Line2("   CPR assist   ");	
				}		
				if(Selected==1){
					send_Line1("  bpm/o2 level  ");
					send_Line2(" --CPR assist-- ");
					Mode=2;				
				}
			}
			if(MenuPos==1){
				if(Selected==0){
					send_Line1(" --CPR assist-- ");
					send_Line2("     options    ");	
					Mode=2;	
				}		
				if(Selected==1){
					send_Line1("   CPR assist   ");
					send_Line2("   --options--  ");	
					Mode=3;	
				}
			}
			if(MenuPos==2){
				if(Selected==0){
					send_Line1("   --options--  ");
					send_Line2("     credits    ");	
					Mode=3;	
				}		
				if(Selected==1){
					send_Line1("     options    ");
					send_Line2("   --credits--  ");	
					Mode=4;	
				}
			}
			if(MenuPos==3){
				if(Selected==0){
					send_Line1("   --credits--  ");
					send_Line2("                ");	
					Mode=4;	
				}		
			}		
		
	}
	if(Switch("PG1")){
		Menu=1;
	}
	if(Switch("PG3")){
		Menu=0;
	}
	if(Menu==0){
		//send_Line1("                ");
		send_Line2("                ");
		if(Mode==1){
			ADCstartconv(1);
			char Sout[16];
			sprintf(Sout,"BPM = %5.i",ADCout(1));
			send_Line1(Sout);
		}
		if(Mode==2){
			BPMcount++;
			Counter++;
			if(BPMcount<10){
				if(A){
					LED_ON("PB13");
				}
				else{
					LED_OFF("PB13");
				}
			}
			if(BPMcount>69){
				BPMcount=0;
			}
		}
		if(Mode==3){
			//--placeholder Options--
		}
		if(Mode==4){
			send_Line1("we're not racist");
			send_Line2("we just hate you");
		}
	}
}
	
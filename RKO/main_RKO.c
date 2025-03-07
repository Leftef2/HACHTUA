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
	//send_Line1("  bpm/o2 level  ");  Choice=1
	//send_Line1("   CPR assist   ");  Choice=2
	//send_Line1("     options    ");  Choice=3
	//send_Line1("     credits    ");  Choice=4
	if(ScrollLocal==0){
		send_Line1("--bpm/o2 level--");
		send_Line2("   CPR assist   ");
		Choice=1;
	}
	if(ScrollLocal==1){
		send_Line1("  bpm/o2 level  ");
		send_Line2(" --CPR assist-- ");
		Choice=2;
	}	
	if(ScrollLocal==2){
		send_Line1(" --CPR assist-- ");
		send_Line2("     options    ");
		Choice=2;
	}	
	if(ScrollLocal==3){
		send_Line1("   CPR assist   ");
		send_Line2("   --options--  ");
		Choice=3;
	}		
	if(ScrollLocal==4){
		send_Line1("   --options--  ");
		send_Line2("     credits    ");
		Choice=3;
	}		
	if(ScrollLocal==5){
		send_Line1("     options    ");
		send_Line2("   --credits--  ");
		Choice=4;
	}	
	if(ScrollLocal==6){
		send_Line1("   --credits--  ");
		send_Line2("                ");
		Choice=4;
	}		
}

int MATHS1(int A[360]){
	int MaxVal=0;
	int MinVal=1000000;
	int Trig=0;
	int TempCount=0;
	int Times[360];
	int AverageTime=0;
	char temp2[17];

	for(int I=0;I<360;I++){
		if(A[I]<MinVal){
			MinVal=A[I];
		}
		if(A[I]>MaxVal){
			MaxVal=A[I];
		}
	}

	int Threshold=MinVal+((MaxVal-MinVal)*0.75);
	sprintf(temp2,"Threshold:%1.i|",(int) Threshold);
	send_Line2(temp2);
	for(int I=0;I<360;I++){
		if(A[I]>Threshold){
			Times[I]=1;
		}
		else{
			Times[I]=0;
		}
	}

	TempCount=0;
	for(int I=0;I<360;I++){
		TempCount=TempCount+Times[I];
	}
	TempCount=TempCount/3;
	return TempCount;
}
int ActiveChoice=0;
int Scroll=0;
int BPM;
char temp[17];
int LED1=0;
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
	ADC_SETUP("PC3",1);
	timer_init();
	Init_DAC2();
	menu(Scroll);
	while(1){
		if(ActiveChoice==0){
			while(!Switch("PG0")&&!Switch("PG2")&&!Switch("PG3")){};
			if(Switch("PG2")){
				Scroll=Scroll+1;
			}
			if(Switch("PG0")){
				Scroll=Scroll-1;
			}
			if(Scroll>=7){
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
			sprintf(temp,"BPM:%1.i|",(int) round(BPM));
			send_Line1(temp);
		}
	}
}


int Counter=0;
int DATAtemp[360];
int Counter2=0;
void TIM2_IRQHandler(void)			//TIMER 2 INTERRUPT SERVICE ROUTINE -- 120 FPS Loop --
{
	Counter2++;
	TIM2->SR&=~TIM_SR_UIF;				//clear interrupt flag in status register
	LED1=!LED1;
	if(LED1==1){
		LED_ON("PF14");
		send_dac((1<<11));
	}
	else{
		LED_OFF("PF14");
		send_dac(0);

	}
	int TempCount=0;	
	if(ActiveChoice==1){//goes into bpm/o2 mode
		ADCstartconv(1);
		if(Counter>360){
			BPM=MATHS1(DATAtemp);
			Counter=0;
		}
		else{
			DATAtemp[Counter]=ADCout(1);
		}
		Counter++;
	}
}
	
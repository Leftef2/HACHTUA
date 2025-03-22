#include <stm32f429xx.h>		//INCLUDE THE HEADER FILE FOR THIS MCU FAMILY
#include <core_cm4.h>
#include "lcd.h"
#include "stdio.h"
#include "my_adc.h"
#include "my_functions.h"
#include "usart.h"
#include "my_switch.h"
#include "timers.h"
#include "my_dac.h"
#include "my_led.h"
#define RunAvSampCount 100  //micro (find and replace)

//BPM valid from 0.4Hz

//global variables go here
int Choice;
int RunValStore[(RunAvSampCount+1)];
int FlipFlop=0;
int Timer_counter;//globals variable for data storage reasons
int TimerControlStore;
int val=0;
int CounterEnable=0;
int ActiveChoice=0;
int Scroll=0;
int CounterSwitch=0;
int Maths_counter;
int LineHasGoneUp=0;

void menu(int ScrollLocal){//when this function is ran, it will send the correct option to LCD
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



void MATHS1(int A){//this will be called every 10ms
	int Average;
	int Counter;
	int Is_Above_Threshold;
	int BPM;
	int MaxSamp=0;
	int MinSamp=10000;
	int Temp;
	float Tolerance;
	char temp[17];//makes a char array which is preassigned with "space"
	
	float Gain=1;
	
	Maths_counter++;
	//-AVERAGING-:
	for(int I=0;I<RunAvSampCount;I++){//run through all samples
		RunValStore[I]=RunValStore[I+1];//Move all the values of the array left by 1 AND LEAVE A SPACE AT THE END e.g. [2,3,4,5,6, ];
	}
	
	RunValStore[RunAvSampCount]=A;//takes the value (given by the adc) and the value to the end of store
	
	for(int I=0;I<RunAvSampCount;I++){
		Temp=Temp+RunValStore[I];//add up all values in store
	}
	if(Maths_counter>RunAvSampCount){
		Average=Temp/RunAvSampCount;
	}
	Temp=0;
	
	//get max/min values to apply to the gain of tolerance value
	for(int I=0;I<RunAvSampCount;I++){
		if(RunValStore[I]<MinSamp){
			MinSamp=RunValStore[I];
		}
		if(RunValStore[I]>MaxSamp){
			MaxSamp=RunValStore[I];
		}		
	}
	Tolerance=((MaxSamp-MinSamp)/10000)*Gain;
	Temp=0;
	Tolerance=0.95;
	// Is current sample above the allowable threshold?:

	if(RunValStore[RunAvSampCount-1]<(RunValStore[RunAvSampCount]-15)){//is last value less than current (line going up)
		LineHasGoneUp=1;
	}
	
	if((RunValStore[RunAvSampCount-1]>(RunValStore[RunAvSampCount])+15)&&LineHasGoneUp==1){
		CounterSwitch=!CounterSwitch;
		LineHasGoneUp=0;
	}
	
	
	if(CounterSwitch){
		LED_ON("PB14");
		Counter++;
	}
	else{
		LED_OFF("PB14");
		BPM=Counter;
		sprintf(temp,"BPM:%1.i|",BPM);
		send_Line1(temp);
		//sprintf(temp,"out:%1.i|",ADCout(1));
		//send_Line2(temp);
		Counter=0;
	}
}



int main(void){
	LED_SETUP("PB14");
	init();//Initialize a bunch of stuff
	menu(0);//after startup splashscreen, go to menu
	while(1){
		if(ActiveChoice==0){
			menu_debounce();
			while(!Switch("PG0")&&!Switch("PG1")&&!Switch("PG2")&&!Switch("PG3")){};//while any button is NOT pressed, do nothing (when button pressed, do stuff)
			if(Switch("PG3")){
				ActiveChoice=Choice;//make the currently selected cursor position equal the variable which controls the "mode"
			}
			if(Switch("PG2")){
				Scroll=Scroll+1;//scroll the menu (down)
			}
			if(Switch("PG0")){
				Scroll=Scroll-1;//scroll the menu (up)
			}
			if(Scroll>8){
				Scroll=0;//if the "cursor" gets to the bottom of the screen, send to top
			}
			if(Scroll<0){
				Scroll=8;//same as above, but opposite
			}
			menu(Scroll);
			while(Switch("PG0")||Switch("PG1")||Switch("PG2")||Switch("PG3")){};//while any button is NOT pressed, do nothing (when button pressed, do stuff)
		}
		if(ActiveChoice==1){
			if(Switch("PG1")){
				ActiveChoice=0;//makes "option" variable go to menu
				menu(Choice);
				//menu_debounce();
			}
		}
	}
}


void TIM2_IRQHandler(void)// -- 10ms Loop --
{
	TIM2->SR&=~TIM_SR_UIF;//clear interrupt flag in status register

	if(ActiveChoice==1){//if in "bpm" mode
		MATHS1(ADCout(1));//Do the maths (send a sample every x ms) and send it to display (via global variable)
		ADCstartconv(1);//start conversion (for next loop);
	}
}
	
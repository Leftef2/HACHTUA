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
int RunAvStore[(RunAvSampCount+1)];
int FlipFlop=0;
int Timer_counter;//globals variable for data storage reasons
int TimerControlStore=0;
int val=0;

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

int MATHS1_RunningAverage(int A){//this will be called every 10ms
	int Average;
	int Counter;
	int Is_line_on_graph_going_up;
	int ReturnVal=0;
	
	
	for(int I=0;I<100;I++){
		RunAvStore[I]=RunAvStore[I+1];//Move all the values of the array left by 1 AND LEAVE A SPACE AT THE END e.g. [2,3,4,5,6, ];
	}
	
	RunAvStore[RunAvSampCount]=A;//takes the value (given by the adc) and adds to store
	
	for(int I=0;I<100;I++){
		Average=Average+RunAvStore[I];//add up all values in store
	}
	
	int Tolerance=500;
	
	Average=Average/RunAvSampCount;//divide by how many samples took
	if(A-Tolerance<Average){//is "line" going down (tolerance is 10)
		Is_line_on_graph_going_up=0;
	}	
	if(A+Tolerance>Average){//is "line" going up (tolerance is 10)
		Is_line_on_graph_going_up=1;
	}
	
	if(Is_line_on_graph_going_up&&(A+Tolerance>Average)){//if the line is going up, flip the switch that controls the timer
		TimerControlStore=0;
	}
	if(Is_line_on_graph_going_up==0&&(A-Tolerance<Average)){
		TimerControlStore=1;
	}

	if(TimerControlStore==0){//when A passes above threshold
		Counter++;
	}
	else{
		Counter=0;
		ReturnVal=Counter;
	}
	
	return TimerControlStore;//return return value
}


int ActiveChoice=0;
int Scroll=0;
int BPM;

int main(void){
	init();//Initialize a bunch of stuff
	menu(0);//after startup splashscreen, go to menu
	while(1){
		if(ActiveChoice==0){
			while(!Switch("PG0")&&!Switch("PG1")&&!Switch("PG2")&&!Switch("PG3")){};//wait for all switch not to be pressed
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
			menu_debounce();
		}
		if(ActiveChoice==1){
			if(Switch("PG1")){
				menu_debounce();
				ActiveChoice=0;//makes "option" variable go to menu
				menu(Choice);
			}

			char temp[17];//makes a char array which is preassigned with "space"
			sprintf(temp,"BPM:%1.i|",BPM);
			send_Line1(temp);
			sprintf(temp,"Val:%1.i|",val);
			send_Line2(temp);
		}
	}
}


void TIM2_IRQHandler(void)// -- 10ms Loop --
{
	TIM2->SR&=~TIM_SR_UIF;//clear interrupt flag in status register
	LED_SETUP("PB14");
	LED_ON("PB14");
	val=ADCout(1);
	if(ActiveChoice==1){//if in "bpm" mode
		BPM=MATHS1_RunningAverage(ADCout(1));//Do the maths (send a sample every x ms) and send it to display (via global variable)
		ADCstartconv(1);//start conversion (for next loop);
	}
}
	
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
#define RunAvSampCount 200  //micro (find and replace)

//BPM valid from 0.4Hz

//global variables go here
int Choice;
int RunValStore[(RunAvSampCount+1)];
int FlipFlop=0;
int Timer_counter;//globals variable for data storage reasons
int TimerControlStore;
int val=0;
int CounterEnable=0;
int ActiveChoice;
int Scroll=0;
int CounterSwitch=0;
int ToleranceStore;

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
	int Is_Above_Peak;
	int BPM;
	int MaxSamp=0;
	int MinSamp=10000;
	int Temp;
	int Tolerance;
	char temp[17];//makes a char array which is preassigned with "space"
	
	ToleranceStore++;
	//-AVERAGING-:
	for(int I=0;I<RunAvSampCount;I++){//run through all samples
		RunValStore[I]=RunValStore[I+1];//Move all the values of the array left by 1 AND LEAVE A SPACE AT THE END e.g. [2,3,4,5,6, ];
	}
	
	RunValStore[RunAvSampCount]=A;//takes the value (given by the adc) and adds to store
	
	for(int I=0;I<RunAvSampCount;I++){
		Average=Average+RunValStore[I];//add up all values in store
	}
	
	
	//make tolerance value based on noise
	if(ToleranceStore>100){
		for(int I=0;I<RunAvSampCount;I++){
			if(I>0){
				Temp=Temp+((RunValStore[I-1]-RunValStore[I])/RunValStore[I]);//add up the difference between values next to eachother as a percentage
			}
		}
		Tolerance=(Temp/(RunAvSampCount-1));
		sprintf(temp,"BPM:%1.i|",Tolerance);
		send_Line1(temp);
		ToleranceStore=0;
}
	// Is current sample above the allowable threshold?:
	

	if(A<Average*Tolerance){//is "line" going down
		Is_Above_Peak=0;
	}	
	if(A>Average*Tolerance){//is "line" going up
		Is_Above_Peak=1;
	}
	
	
	//-If above allowable threshold:
	
	if(Is_Above_Peak){//if above threshold and Counter is NOT COUNTING
		CounterSwitch=!CounterSwitch;//switch the Counter
	}
	
	if(CounterSwitch){
		LED_ON("PB14");
		Counter++;
	}
	else{
		LED_OFF("PB14");
		//BPM=Counter;
		//sprintf(temp,"BPM:%1.i|",BPM);
		//send_Line1(temp);
	}
}



int main(void){
	LED_SETUP("PB14");
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
	
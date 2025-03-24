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
int FlipFlop=0; //globals variable for data storage reasons
int CounterEnable=0;
int ActiveChoice=0;
int Scroll=0;
int CounterSwitch=0;
int LineHasGoneUp=0;
float Counter;
int Counter2;
int Counter3;
int StopLoop=0;
int StopLoop1=0;
int Average;
int AverageVal;
int BuzzStopLoop1=0;
int BuzzStopLoop2=0;
int SubMenu=0;
char temp[17];//makes a char array which is preassigned with "space"

void menu(int ScrollLocal){//when this function is ran, it will send the correct option to LCD
	//send_Line1("      bpm       ");  Choice=1
	//send_Line1("  ADC voltage   ");  Choice=2
	//send_Line1(" PSC/ARR values ");  Choice=3
	//send_Line1("   CPR assist   ");  Choice=4
	//send_Line1("     credits    ");  Choice=5

	if(ScrollLocal==0){
		send_Line1("    --bpm--     ");
		send_Line2("  ADC voltage   ");
		Choice=1;
	}
	if(ScrollLocal==1){
		send_Line1("      bpm       ");
		send_Line2("--ADC voltage-- ");
		Choice=2;
	}	
	if(ScrollLocal==2){
		send_Line1("--ADC voltage-- ");
		send_Line2(" PSC/ARR values ");
		Choice=2;
	}	
	if(ScrollLocal==3){
		send_Line1("  ADC voltage   ");
		send_Line2("-PSC/ARR values-");
		Choice=3;
	}		
	if(ScrollLocal==4){
		send_Line1("-PSC/ARR values-");
		send_Line2("   CPR assist   ");
		Choice=3;
	}		
	if(ScrollLocal==5){
		send_Line1(" PSC/ARR values ");
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

//things to do:
//SPI
//USART
//i2C
//led array

void MATHS1(int A){//this will be called every 10ms
	int Is_Above_Threshold;
	int MaxSamp=0;
	int MinSamp=10000;
	int Temp;
	float Tolerance;
	
	int Tune=120;
	
	for(int I=0;I<RunAvSampCount;I++){//run through all samples
		RunValStore[I]=RunValStore[I+1];//Move all the values of the array left by 1 AND LEAVE A SPACE AT THE END e.g. [2,3,4,5,6, ];
	}
	
	RunValStore[RunAvSampCount]=A;//takes the value (given by the adc) and the value to the end of store
	
//	for(int I=0;I<RunAvSampCount;I++){
//		Temp=Temp+RunValStore[I];//add up all values in store
//	}
//	Average=Temp/RunAvSampCount;
//	Temp=0;
	
	
	//get max/min values to apply to the gain of tolerance value
//	for(int I=0;I<RunAvSampCount;I++){
//		if(RunValStore[I]<MinSamp){
//			MinSamp=RunValStore[I];
//		}
//		if(RunValStore[I]>MaxSamp){
//			MaxSamp=RunValStore[I];
//		}		
//	}
//	Tolerance=((MaxSamp-MinSamp)/10000)*Gain;

	if(RunValStore[RunAvSampCount-1]<(RunValStore[RunAvSampCount]-Tune)){//is last value less than current (line going up)
		LineHasGoneUp=1;
	}
	
	else if((RunValStore[RunAvSampCount-1]>(RunValStore[RunAvSampCount])+Tune)&&LineHasGoneUp==1){
		CounterSwitch=!CounterSwitch;
		LineHasGoneUp=0;
	}
	
	if(CounterSwitch){
		LED_ON("PB14");
		StopLoop=1;
		Counter++;
	}
	else if(StopLoop==1){
		Shortbuzz();
		LED_OFF("PB14");
		int BPM=(int)round((1.0f/(Counter/100))*60);
		Average=Average+BPM;
		Counter3++;
		StopLoop=0;
		if(BPM<20){
			send_Line1("BPM: Invalid");
			send_Line2("Average:");
		}
		else if(BPM>300){
			send_Line1("BPM: Invalid");
			send_Line2("Average:");
		}
		else{
		sprintf(temp,"BPM:%1.i|",BPM);
		send_Line1(temp);
		sprintf(temp,"Average BPM:%1.i|",AverageVal);//yes it is 15s
		send_Line2(temp);
		}
		Counter=0;
	}

}

void Conversion(int A){
	send_Line1("12 bit*805.67uV");
	sprintf(temp,"=%.4fV",A*0.00080567f);
	send_Line2(temp);
	if(Switch("PG1")){
		ActiveChoice=0;//makes "option" variable go to menu
		menu(Choice);
	}
}

int main(void){
	LED_SETUP("PB14");
	init();//Initialize a bunch of stuff
	menu(0);//after startup splashscreen, go to menu
	while(1){
		if(ActiveChoice==0){
			StopLoop1=0;
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
			menu_debounce();
		}
		if(ActiveChoice==1){
			if(StopLoop1==0){
				send_Line1("BPM: Loading..");
				send_Line2("Average:");
				StopLoop1=1;
			}
			if(Switch("PG1")){
				ActiveChoice=0;//makes "option" variable go to menu
				menu(Choice);
			}
		}
		if(ActiveChoice==3){
			if(SubMenu==0){
				sprintf(temp,"PSC=%1.i",TIM2->PSC);//get the value of PSC for TIM2 and send to LCD
				send_Line1(temp);
				sprintf(temp,"ARR=%1.i ->",TIM2->ARR);
				send_Line2(temp);
			
				if(Switch("PG1")){
					menu_debounce();
					while(Switch("PG0")|Switch("PG1")|Switch("PG2")|Switch("PG3")){};//without debounce and while, buttons go through menu too quick
					ActiveChoice=0;//makes "option" variable go to menu
					menu(Scroll);
				}
				if(Switch("PG3")){
					menu_debounce();
					while(Switch("PG0")|Switch("PG1")|Switch("PG2")|Switch("PG3")){};
					SubMenu=1;
				}
			}
			if(SubMenu==1){				
				send_Line1("system= 180MHz");
				send_Line2("APB = 180MHz/2");
				if(Switch("PG3")){
					menu_debounce();
					while(Switch("PG0")|Switch("PG1")|Switch("PG2")|Switch("PG3")){};
					SubMenu=2;
				}
				if(Switch("PG1")){
					menu_debounce();
					while(Switch("PG0")|Switch("PG1")|Switch("PG2")|Switch("PG3")){};
					SubMenu=0;
				}
			}
			if(SubMenu==2){				
				send_Line1("APB=90MHz");
				send_Line2("90MHz/256=351KHz");
				if(Switch("PG3")){
					menu_debounce();
					while(Switch("PG0")|Switch("PG1")|Switch("PG2")|Switch("PG3")){};
					SubMenu=3;
				}
				if(Switch("PG1")){
					 menu_debounce();
					while(Switch("PG0")|Switch("PG1")|Switch("PG2")|Switch("PG3")){};
					SubMenu=1;
				}
			}
			if(SubMenu==3){				
				sprintf(temp,"ARR=%1.i",TIM2->ARR);
				send_Line1(temp);
				send_Line2("Time=ARR*1/351KHz");
				if(Switch("PG3")){
					menu_debounce();
					while(Switch("PG0")|Switch("PG1")|Switch("PG2")|Switch("PG3")){};
					SubMenu=4;
				}
				if(Switch("PG1")){
					 menu_debounce();
					while(Switch("PG0")|Switch("PG1")|Switch("PG2")|Switch("PG3")){};
					SubMenu=2;
				}
			}
			if(SubMenu==4){				
				sprintf(temp,"Time=%.4fs",(TIM2->ARR)*(1.0f/350000));
				send_Line1(temp);
				send_Line2("Press D for menu");
				if(Switch("PG3")){
					menu_debounce();
					while(Switch("PG0")|Switch("PG1")|Switch("PG2")|Switch("PG3")){};
					SubMenu=0;
					ActiveChoice=0;
					menu(Scroll);
				}
				if(Switch("PG1")){
					 menu_debounce();
					while(Switch("PG0")|Switch("PG1")|Switch("PG2")|Switch("PG3")){};
					SubMenu=3;
				}
			}
		}
		if(ActiveChoice==4){
			send_Line1("110 BPM");
			send_Line2("B for menu");
			if(Switch("PG1")){
				menu_debounce();
				while(Switch("PG0")|Switch("PG1")|Switch("PG2")|Switch("PG3")){};
				menu(Scroll);
				ActiveChoice=0;
			}
		}
		if(ActiveChoice==5){
			send_Line1("Sigma Co.");
			send_Line2("Copyright 2025");
			if(Switch("PG1")){
				menu_debounce();
				while(Switch("PG0")|Switch("PG1")|Switch("PG2")|Switch("PG3")){};
				menu(Scroll);
				ActiveChoice=0;
			}
		}
	}
}


void TIM2_IRQHandler(void)// -- 10ms Loop --
{
	TIM2->SR&=~TIM_SR_UIF;//clear interrupt flag in status register
	
	if(ActiveChoice==1){//if in "bpm" mode
		Counter2++;
		MATHS1(ADCout(1));//Do the maths (send a sample every x ms) and send it to display (via global variable)
		ADCstartconv(1);//start conversion (for next loop);
		if(Counter2>1500){
			AverageVal=Average/Counter3;
			Average=0;
			Counter2=0;
			Counter3=0;
		}
	}
	if(ActiveChoice==2){
		ADCstartconv(1);
		Conversion(ADCout(1));
	}
	if(ActiveChoice==4){
		Counter2++;
		if(Counter2>55){
			Shortbuzz();
			Counter2=0;
		}
	}
			
}
	
#include "my_functions.h"
#include <stdlib.h>
#define menu_debounce 5000;	// set menu_deboune equal to 5ms 
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
void menu_debounce_function(void)         //blocking delay for LCD, argument is approximate number of micro-seconds to delay
{
	unsigned char i;
	int Time=menu_debounce;									//ste Time equal to menu_debounce
	while(Time--)
	{
		for(i=0; i<SystemCoreClock/4000000; i++){__NOP();}
	}
}
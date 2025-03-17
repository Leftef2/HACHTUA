#include "my_functions.h"
#include <stdlib.h>
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
	for(int i=0; i<13000000; i++){__NOP();}
}
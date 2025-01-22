#include "my_functions.h"
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
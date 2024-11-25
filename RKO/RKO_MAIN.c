#include <stm32f429xx.h>		//INCLUDE THE HEADER FILE FOR THIS MCU FAMILY
void delay (void)
{	
	volatile unsigned int i;		//create variable
	for (i=0; i<1000000; i++);	//WAIT count to 1 million 
}
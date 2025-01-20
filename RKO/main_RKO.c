#include <stm32f429xx.h>		//INCLUDE THE HEADER FILE FOR THIS MCU FAMILY
#include <core_cm4.h>
#include "lcd.h"
#include "stdio.h"
#include <string.h>
#include <stdlib.h>
#include "my_adc.h"
#include "my_led.h"
int getN(char* str){
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
//void LED_INIT (void)
//{
//	//ENABLE PORT(S)
//	//RCC->AHB1ENR |= 0x02;						//use label defined in stm32f4.h instead of hex value: easier to read and change
//	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;	//ONLY GPIO B clock enable
//	
//	//CONFIGURE PORT:GPIOB  PIN:0 TO OUTPUT for LED1
//	GPIOB->MODER |= (1<<0);						//ONLY set  GPIOB0
//	// the above assumes that bit 1 is to zero
//	GPIOB->MODER &= ~(0<<1);					//ONLY clear GPIOB1
//	
//	//CONFIGURE PORT:GPIOB  PIN:7 TO OUTPUT for LED2
//	GPIOB->MODER |= (1<<14);						//ONLY set  GPIOB7
//	
//	//CONFIGURE PORT:GPIOB  PIN:14 TO OUTPUT for LED3
//	GPIOB->MODER |= (1<<28);						//ONLY set  GPIOB14


//}	
//void LED1_ON (void)
//{
//			GPIOB->ODR |= 1;							//ONLY TURN LED ON
//}

//void LED1_OFF (void)
//{
//			GPIOB->ODR &= ~1;							//ONLY TURN LED ON
//}
//void LED2_ON (void)
//{
//			GPIOB->ODR |= (1<<7);							//ONLY TURN LED ON
//}

//void LED2_OFF (void)
//{
//			GPIOB->ODR &= ~(1<<7);							//ONLY TURN LED ON
//}
//void LED3_ON (void)
//{
//			GPIOB->ODR |= (1<<14);							//ONLY TURN LED ON
//}

//void LED3_OFF (void)
//{
//			GPIOB->ODR &= ~(1<<14);							//ONLY TURN LED ON
//}
int main(void){
  int A;
	initLCD();
	ADC_SETUP("PA0",1);//sets up PA0 and selects which ADC to use
	LED_SETUP("PB0");
	LED_SETUP("PB7");
	LED_SETUP("PB14");
	clr_LCD_RS();
	char Sout[20];
	while(1){
		ADCstartconv(1);				//start ADC conversion
//		sprintf(Sout,"output is= %5.i\n",ADCout(1));
		char Test[4]="PB12";
		sprintf(Sout,"output is= %5.i\n",getN(Test));
		cmdLCD(LCD_LINE1);
		for(A=0;A<sizeof(Sout);A++){
			WaitLcdBusy();
			putLCD(Sout[A]);
		};
		sprintf(Sout,"                  \n");
		cmdLCD(LCD_LINE2);
		for(A=0;A<sizeof(Sout);A++){
			WaitLcdBusy();
			putLCD(Sout[A]);
		};

		if(ADCout(1)<1366){
			LED_ON("PB0");
		}
		else{
			LED_OFF("PB0");
		}
		if(1366<ADCout(1)&ADCout(1)<2732){
			LED_ON("PB7");
		}
		else{
			LED_OFF("PB7");
		}
		if(ADCout(1)>2732){
			LED_ON("PB14");
		}
		else{
			LED_OFF("PB14");
		}		

	}
}

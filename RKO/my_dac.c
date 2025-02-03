#define DAC_pin 5
#include "my_dac.h"
#include "wait.h"

#include <math.h>
void Init_DAC2(void)
{
	
//Enable the clock for GPIO Port A
RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;
//Configure the PoRT A pin 5 to be the Analogue
GPIOA->MODER|=(3u<<(2*DAC_pin));
//Enable the clock for DAC module
RCC->APB1ENR|=RCC_APB1ENR_DACEN;
//Enable the DAC
DAC->CR|=DAC_CR_EN2;
}

int m;
void Ramp_Output (void){		//Ramp output
	while(1){									//Enter While loop
		for(m=0; m<3000; m++){	//Ramp up
			DAC->DHR12R2=m;				// Print to DAC
		}
		for(m=3000; m>0; m--){	//Ramp Down
			DAC->DHR12R2=m;				// Print to DAC
		}
	}}

int q;										// Set Int
int w;										// Set Int
	void Square_Output (void){	//square output
		while (1){
			q=0;								// Set Int
			DAC->DHR12R2=q;			// Print to DAC
			Delay_ms(1);				//Delay
			w=3000;							// Set Int
			DAC->DHR12R2=w;			// Print to DAC
			Delay_ms(1);				//Delay
		}
		}
	int r;										// Set Int
			void DC_level(void){	//DC Level 
				r=3000;							// Set value
			}
				
			
			int j;
void Complex_Output (void){		//Ramp output
		while(1){									//Enter While loop
		for(m=0; m<3000; m++){	//Ramp up
			DAC->DHR12R2=m;				// Print to DAC
		}
//		for(m=3000; m>0; m--){	//Ramp Down
//			DAC->DHR12R2=m;				// Print to DAC
//		}
			for(m=0; m<1000; m++){	//Ramp up
			DAC->DHR12R2=m;				// Print to DAC
		}
		for(m=1000; m>0; m--){	//Ramp Down
			DAC->DHR12R2=m;				// Print to DAC
		}
	}
	
	
	
//			DAC->DHR12R2=m;				// Print to DAC
//		}
//			void Sin_Output (void){
//	
//			float volts;
//			float frequency;
//			float offset;
//			float duration;
//			float val;
//			long y, end;
//				
//				volts=2;
//				offset=10;
//				frequency=2000;
//				duration=0.1;
//				
//				end = (duration*100000);
//				for(y=0;y< end; y++){
//					val=_sin (frequency*(((float) 1)/5)*2*3.1415926);
//					DAC->DHR12R2 = (val*volts)+offset;
//					swatch (0.00001);
//		}
//	}
}
		
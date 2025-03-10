#define DAC_pin 5
#include "my_dac.h"

#include <math.h>
void Init_DAC2(void)
{
	
//	float f = sin(2*3.14*1.0*0);
//	2*pi*f*t
//	
//	t=Ts*n
//	Ts = sample TIME (1/Fs)
//	n = sample_num
	
//Enable the clock for GPIO Port A
RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;
//Configure the PoRT A pin 5 to be the Analogue
GPIOA->MODER|=(3u<<(2*DAC_pin));
//Enable the clock for DAC module
RCC->APB1ENR|=RCC_APB1ENR_DACEN;
//Enable the DAC
DAC->CR|=DAC_CR_EN2;
}
void send_dac(int a){
	DAC->DHR12R2=a;
}
	
	
int m;
void Ramp_Output (void){
	while(1){
		for(m=0; m<3000; m++){
			DAC->DHR12R2=m;
		}
		for(m=3000; m>0; m--){
			DAC->DHR12R2=m;
		}
	}}

//int q;
//int w;	
//	void Square_Output (void){
//		while (1){
//			q=0;
//			DAC->DHR12R2=q;
//			Delay_ms(1);
//			w=3000;
//			DAC->DHR12R2=w;
//			Delay_ms(1);
//		}
//		}
//	int r;
//			void DC_level(void){
//				r=3000;
//			}
				
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
		
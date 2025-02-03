#include "wait.h"

/*Generate ms */
void Delay_ms(volatile int time_ms)
{
            int j;
        for(j = 0; j < time_ms*4000; j++)
            {}  /* excute NOP for 1ms */
}
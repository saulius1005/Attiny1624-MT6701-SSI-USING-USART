/*
 * main.c
 *
 * Created: 2025-02-27 17:58:36
 *  Author: Saulius
 */ 

#include "Settings.h"

int main(void)
{
    CLOCK_INHF_clock_init();
    GPIO_init();
    USART0_init();
    while (1) 
    {
		MT6701_SSI_Angle(); //Reading sensor every ~100mS
		_delay_ms(100);
	}
}

/*
 * main.c
 *
 * Created: 2025-02-27 17:58:36
 *  Author: Saulius
 */ 

#include "Settings.h"
 
volatile uint32_t received_data = 0;

int main(void)
{
    CLOCK_INHF_clock_init();
    GPIO_init();
    USART0_init();

    while (1) 
    {
		USART0.STATUS = USART_TXCIF_bm; //clearing frame flag before data collecting
		PORTA.OUTCLR = PIN7_bm; //SS Low
			for (uint8_t i = 0; i<3; i++){ // 3x8 = 24bits of data
				USART0_sendChar('o');// sending dummy data  (8bits) for XCK generation
				uint8_t received_byte = USART0_readChar();  // reading 8 bits
				received_data <<= 8;  // shift previous data to left
				received_data |= received_byte;  // and add current data
			}	
		while(!(USART0.STATUS & USART_TXCIF_bm)){}// waiting until all frame will be send
		PORTA.OUTSET = PIN7_bm; //only after turn off selection pin (turn on high) (USART SPI MODE dont have integrated SS controll)
		received_data = 0; //reseting value
		_delay_ms(10);// do pause for debugging
	}
}

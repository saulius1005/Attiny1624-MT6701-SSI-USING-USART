/**
 * GPIO.c
 * 
 * Created: 2024-12-04 16:54:46
 * Author: Saulius
 */

#include "Settings.h"

void GPIO_init(){
    PORTMUX.USARTROUTEA = PORTMUX_USART0_DEFAULT_gc; // Set USART0 to default pins

    PORTB.DIRSET = PIN1_bm | PIN2_bm; // Set PB1 as XCK (MT6701 CLK) out and PB2 as TX for dummy data sending
	PORTB.PIN2CTRL = PORT_PULLUPEN_bm; // Enable pull-up for PB2 (USART0 TX)
	//PORTB.PIN1CTRL = PORT_INVEN_bm; //For mt6701 need to use not inverted pin with enabled UCPHA (view USART.c). Uncomment if need to invert
    PORTB.DIRCLR = PIN3_bm; // Set PA3 as input (USART0 RX as MISO (MT6701 DO))
    PORTB.PIN3CTRL = PORT_PULLUPEN_bm; // Enable pull-up for PB3 (USART0 RX)

	PORTA.DIRSET = PIN7_bm; // Set PA7 set as SS (MT6701 CSN)
	PORTA.OUTSET = PIN7_bm; // and keep it high
}

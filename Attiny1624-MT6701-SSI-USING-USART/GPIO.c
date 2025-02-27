/**
 * @file GPIO.c
 * @brief GPIO Initialization for various peripherals and sensors
 * 
 * This file contains the initialization of GPIO pins for communication peripherals such as USART, TWI,
 * and for managing input/output for keypad and sensor interfaces. It configures the appropriate pins for
 * USART, I2C, and other functionalities like keypad scanning and sensor input.
 * 
 * Created: 2024-12-04 16:54:46
 * Author: Saulius
 */

#include "Settings.h"

/**
 * @brief Initializes GPIO pins for USART, TWI, keypad, and sensor interfaces.
 * 
 * This function configures the GPIO pins for various communication protocols and sensors. 
 * - Sets USART0 and USART1 pins for transmitting/receiving data.
 * - Configures I2C pins (SDA and SCL) for communication.
 * - Initializes keypad pins (rows and columns) for input.
 * - Configures ADC pins for wind speed, wind direction, and sun light sensor readings.
 * 
 * It also configures pull-up resistors for specific pins and sets the appropriate output logic levels.
 */
void GPIO_init(){
    // Configure USART0 and USART1 pin routing
    PORTMUX.USARTROUTEA = PORTMUX_USART0_DEFAULT_gc | PORTMUX_USART1_DEFAULT_gc; // Set USART0 to alternative pins set 1, USART1 to default pins

    PORTB.DIRSET = PIN1_bm; // Set PB2 as XCK out
	//PORTB.OUTSET = PIN1_bm;// set xck high
	//PORTB.PIN1CTRL = PORT_INVEN_bm;
    PORTB.DIRCLR = PIN3_bm; // Set PA3 as input (USART0 RX)
    PORTB.PIN3CTRL = PORT_PULLUPEN_bm; // Enable pull-up for PA3 (USART0 RX)

	PORTA.DIRSET = PIN7_bm; // Set PA7 set as SS
	PORTA.OUTSET = PIN7_bm;
}

/**
 * @file GPIO.c
 * @brief GPIO initialization for MT6701 sensor communication.
 * @author Saulius
 * @date 2024-12-04
 */

#include "Settings.h"

/**
 * @brief Initializes GPIO pins for USART0 SPI communication with the MT6701 sensor.
 *
 * Configures:
 * - PB1 as XCK (MT6701 CLK) output.
 * - PB2 as TX for dummy data sending with pull-up enabled.
 * - PB3 as RX (MISO, MT6701 DO) with pull-up enabled.
 * - PA7 as SS (MT6701 CSN) output, initially set high.
 */
void GPIO_init(){
    PORTMUX.USARTROUTEA = PORTMUX_USART0_DEFAULT_gc; ///< Set USART0 to default pins

    PORTB.DIRSET = PIN1_bm | PIN2_bm; ///< Set PB1 as XCK (MT6701 CLK) out and PB2 as TX for dummy data sending
    PORTB.PIN2CTRL = PORT_PULLUPEN_bm; ///< Enable pull-up for PB2 (USART0 TX)
    //PORTB.PIN1CTRL = PORT_INVEN_bm; ///< Uncomment if signal inversion is needed
    
    PORTB.DIRCLR = PIN3_bm; ///< Set PB3 as input (USART0 RX as MISO (MT6701 DO))
    PORTB.PIN3CTRL = PORT_PULLUPEN_bm; ///< Enable pull-up for PB3 (USART0 RX)

    PORTA.DIRSET = PIN7_bm; ///< Set PA7 as SS (MT6701 CSN)
    PORTA.OUTSET = PIN7_bm; ///< Keep SS high
}

/**
 * @file USART.c
 * @brief Implementation of USART communication in SPI mode.
 * @author Saulius
 * @date 2025-02-10
 */

#include "Settings.h"

/**
 * @brief Initializes USART0 for SPI communication.
 *
 * This function configures USART0 to operate in SPI master mode with a baud rate of 500 kbps.
 * It enables the receiver (MISO) and transmitter (for sending dummy data), and sets
 * the SPI mode with data sampling on the trailing edge.
 */
void USART0_init() {
    USART0.BAUD = (uint16_t)USART0_BAUD_RATE(500000); ///< Set baud rate to 0.5 Mbps
    USART0.CTRLB = USART_RXEN_bm | USART_TXEN_bm; ///< Enable RX as MISO, TX for dummy data sending
    USART0.CTRLC = USART_CMODE_MSPI_gc | USART_UCPHA_bm; ///< Configure as Host SPI, data sampled on the trailing edge
}

/**
 * @brief Sends a character via USART0.
 *
 * @param c Character to be transmitted.
 *
 * This function waits for the data register to be empty before transmitting
 * the provided character.
 */
void USART0_sendChar(char c) {
    while (!(USART0.STATUS & USART_DREIF_bm)); ///< Wait for data register to be empty
    USART0.TXDATAL = c; ///< Send character
}

/**
 * @brief Reads a character from USART0.
 *
 * @return The received character.
 *
 * This function clears the receive buffer before reading and waits
 * for data to be received before returning the character.
 */
char USART0_readChar() {
    USART0.STATUS = USART_RXCIF_bm; ///< Clear buffer before reading
    while (!(USART0.STATUS & USART_RXCIF_bm)); ///< Wait for data to be received
    return USART0.RXDATAL; ///< Return received character
}

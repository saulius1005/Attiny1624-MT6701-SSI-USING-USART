/*
 * USART.c
 *
 * Created: 2025-02-10 19:23:14
 * Author: Saulius
 *
 */

#include "Settings.h"


void USART0_init() {
	USART0.BAUD = (uint16_t)USART0_BAUD_RATE(500000); // Set baud rate to 0.5 Mbps
	USART0.CTRLB = USART_RXEN_bm | USART_TXEN_bm; // Enable RX as MISO, TX for dummy data sending
	USART0.CTRLC = USART_CMODE_MSPI_gc | USART_UCPHA_bm; // Configure as Host SPI and Data are sampled on the trailing (last) edge
}

void USART0_sendChar(char c) {
	while (!(USART0.STATUS & USART_DREIF_bm)); // Wait for data register to be empty
	USART0.TXDATAL = c; // Send character
}

char USART0_readChar() {
	USART0.STATUS = USART_RXCIF_bm; // Clear buffer before reading
	while (!(USART0.STATUS & USART_RXCIF_bm)); // Wait for data to be received
	return USART0.RXDATAL; // Return received character
}
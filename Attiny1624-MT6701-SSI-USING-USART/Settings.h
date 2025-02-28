/*
 * Settings.h
 *
 * Created: 2024-12-04 17:00:49
 * Author: Saulius
 * 
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#define F_CPU 20000000

#define USART0_BAUD_RATE(BAUD_RATE) ((float)(F_CPU / (2 *(float)BAUD_RATE / 64)) + 0.5)//Synchronous mode as Host SPI

#include <avr/io.h>
#include <avr/cpufunc.h>
#include <util/delay.h>
#include "MT6701.h"

void GPIO_init();

void CLOCK_INHF_clock_init();

uint8_t CRC(uint32_t command);

void USART0_init();

void USART0_sendChar(char c);

char USART0_readChar();

uint8_t MT6701CRC(uint32_t *data);

void MT6701_SSI_Angle();

#endif /* SETTINGS_H_ */
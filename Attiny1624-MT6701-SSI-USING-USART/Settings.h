/*
 * Settings.h
 *
 * Created: 2024-12-04 17:00:49
 * Author: Saulius
 * 
 * @brief This header file contains function prototypes, macros, and includes necessary for configuring hardware,
 *        managing communication protocols (I2C, USART), and interacting with various sensors and peripherals.
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#define F_CPU 20000000

#define TIMEOUT_COUNTER 500000 ///< Timeout counter value for operations

#define USART0_BAUD_RATE(BAUD_RATE) ((float)(F_CPU / (2 *(float)BAUD_RATE / 64)) + 0.5)//Synchronous mode

#define USART1_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (8 *(float)BAUD_RATE)) + 0.5) //Asynchronous double speed mode. For normal mode instead 8 use 16

#include <avr/io.h>      /**< Include AVR I/O library for register definitions and hardware control */
#include <avr/cpufunc.h>
#include <util/delay.h>
#include <stdio.h>       /**< Include standard I/O library for functions like printf */
#include <string.h>      /**< Include string library for handling string functions like strlen */

void GPIO_init();

void CLOCK_INHF_clock_init();

uint8_t CRC(uint32_t command);

void USART0_init();

void USART0_sendChar(char c);

void USART0_sendString(char *str);

int USART0_printChar(char c, FILE *stream);

char USART0_readChar();

void USART1_init();

void USART1_sendChar(char c);

void USART1_sendString(char *str);

int USART1_printChar(char c, FILE *stream);

char USART1_readChar();

void USART_printf(uint8_t usart_number, const char *format, ...);

#endif /* SETTINGS_H_ */
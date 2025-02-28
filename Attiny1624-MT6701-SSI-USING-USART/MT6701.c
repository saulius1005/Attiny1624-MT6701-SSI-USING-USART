/*
 * MT6701.c
 *
 * Created: 2025-02-28 18:06:57
 *  Author: Saulius
 */ 
 #include "Settings.h"
 #include "MT6701Var.h"

 void MT6701_SSI_Angle(){
	uint32_t received_data = 0;
 	USART0.STATUS = USART_TXCIF_bm; //clearing frame flag before data collecting
 	PORTA.OUTCLR = PIN7_bm; //pull CSN Low
 	while(!(USART0.STATUS & USART_TXCIF_bm)){
	 	for (uint8_t i = 0; i<3; i++){ // 3x8 = 24bits of data
		 	USART0_sendChar('o');// sending dummy data  (8bits) for XCK (CLK) generation
		 	uint8_t received_byte = USART0_readChar();  // reading 8 bits of data (DO)
		 	received_data <<= 8;  // shift previous data to left
		 	received_data |= received_byte;  // and add current data
	 	}
 	}// repeating until all frame will be send
 	PORTA.OUTSET = PIN7_bm; //pull CSN on high (USART SPI MODE don't have integrated SS (CSN) control

	MT6701.CRCError = MT6701CRC(&received_data); // check and remove crc from received data
	MT6701.MagneticFieldStatus = (received_data & 0xf) & 0x3; //extracting magnetic field status
	MT6701.PushButtonStatus = (received_data & 0xf) & 0x4; //extracting push button status
	MT6701.TrackStatus = (received_data & 0xf) & 0x8; // extrackting track status
	MT6701.Angle = (double)(received_data >> 4)/45.51111111; //45.511... same as (received_data>>4) / 16384 * 360

 }
/*
 * CRC.c
 *
 * Created: 2024-12-04 18:26:29
 * Author: Saulius
 */

 #include "Settings.h"

// CRC-6 (X^6 + X + 1) lookup table
const uint8_t crc6_table[64] = {
	0x00, 0x03, 0x06, 0x05, 0x0C, 0x0F, 0x0A, 0x09,
	0x18, 0x1B, 0x1E, 0x1D, 0x14, 0x17, 0x12, 0x11,
	0x30, 0x33, 0x36, 0x35, 0x3C, 0x3F, 0x3A, 0x39,
	0x28, 0x2B, 0x2E, 0x2D, 0x24, 0x27, 0x22, 0x21,
	0x23, 0x20, 0x25, 0x26, 0x2F, 0x2C, 0x29, 0x2A,
	0x3B, 0x38, 0x3D, 0x3E, 0x37, 0x34, 0x31, 0x32,
	0x13, 0x10, 0x15, 0x16, 0x1F, 0x1C, 0x19, 0x1A,
	0x0B, 0x08, 0x0D, 0x0E, 0x07, 0x04, 0x01, 0x02,
};

// Optimizuotas CRC-6 skaièiavimas naudojant lookup lentelæ
uint8_t crc6_mt6701_lookup(uint32_t data) {
	return crc6_table[crc6_table[crc6_table[0 ^ ((data >> 12) & 0x3F)] ^ ((data >> 6) & 0x3F)] ^ (data & 0x3F)];
}

uint8_t MT6701CRC(uint32_t *data){ //function modifies init data values by removing crc (last 6 bites) and return 0 if crc is correct
    uint8_t received_crc = *data & 0x3F; //extracting only crc from data
    *data = *data >> 6;   // removing crc and leaving only real data (without CRC)
    uint8_t calculated_crc = crc6_mt6701_lookup(*data);
	return received_crc == calculated_crc ? 0 : 1; //return 0 if crc is correct and 1 if not
}

/* simpler version using lookup table (not optimized)
#include <stdio.h>
#include <stdint.h>

// Precalculiuota CRC-6 (X^6 + X + 1) lookup lentelë
const uint8_t crc6_table[64] = {
	0x00, 0x03, 0x06, 0x05, 0x0C, 0x0F, 0x0A, 0x09,
	0x18, 0x1B, 0x1E, 0x1D, 0x14, 0x17, 0x12, 0x11,
	0x30, 0x33, 0x36, 0x35, 0x3C, 0x3F, 0x3A, 0x39,
	0x28, 0x2B, 0x2E, 0x2D, 0x24, 0x27, 0x22, 0x21,
	0x23, 0x20, 0x25, 0x26, 0x2F, 0x2C, 0x29, 0x2A,
	0x3B, 0x38, 0x3D, 0x3E, 0x37, 0x34, 0x31, 0x32,
	0x13, 0x10, 0x15, 0x16, 0x1F, 0x1C, 0x19, 0x1A,
	0x0B, 0x08, 0x0D, 0x0E, 0x07, 0x04, 0x01, 0x02,
};

// CRC-6 skaièiavimas naudojant lookup lentelæ
uint8_t crc6_mt6701_lookup(uint32_t data) {
	uint8_t crc = 0;
	
	// 18 bitø duomenys dalijami á 6 bitø dalis lookup lentelës indeksavimui
	crc = crc6_table[crc ^ ((data >> 12) & 0x3F)];
	crc = crc6_table[crc ^ ((data >> 6) & 0x3F)];
	crc = crc6_table[crc ^ (data & 0x3F)];
	
	return crc;
}

int main() {
	uint32_t raw_data = 0x6C6431; //testavimo eilutë gauta ið mt6701
	uint32_t data = raw_data >> 6;
	uint8_t received_crc = raw_data & 0x3F;
	uint8_t calculated_crc = crc6_mt6701_lookup(data);

	printf("Gautas CRC: 0x%02X, Apskaièiuotas CRC: 0x%02X\n", received_crc, calculated_crc);
	printf(calculated_crc == received_crc ? "CRC teisingas!\n" : "CRC klaida!\n");

	return 0;
}

*/ 



/* //CRC calculation without lookup table
#include <stdio.h>
#include <stdint.h>

#define CRC6_POLY  0x43  // X^6 + X + 1
#define CRC6_INIT  0x00  // Pradinis CRC

uint8_t crc6_mt6701_bitwise(uint32_t data) {
	uint8_t crc = CRC6_INIT;
	
	// 18 bitø duomenø perdirbimas
	for (int i = 17; i >= 0; i--) {
		uint8_t bit = (data >> i) & 1;
		crc = ((crc << 1) | bit) & 0x3F;
		if (crc & 0x20) {  // Jei aukðèiausias bitas (6 bitas) yra 1, atliekamas XOR su polinomu
			crc ^= CRC6_POLY;
		}
	}
	return crc;
}

int main() {
	uint32_t raw_data = 0x6C6431;
	uint32_t data = raw_data >> 6;  // Paðaliname paskutinius 6 bitus (CRC)
	uint8_t received_crc = raw_data & 0x3F;  // Paskutiniai 6 bitai – tai CRC
	uint8_t calculated_crc = crc6_mt6701_bitwise(data);

	printf("Gautas CRC: 0x%02X, Apskaièiuotas CRC: 0x%02X\n", received_crc, calculated_crc);
	printf(calculated_crc == received_crc ? "CRC teisingas!\n" : "CRC klaida!\n");

	return 0;
}

*/

/* //lookup table generation
#include <stdio.h>
#include <stdint.h>
#define CRC6_POLY  0x43

uint8_t crc6_generate(uint8_t data) {
	uint8_t crc = data;
	for (int i = 0; i < 6; i++) {
		if (crc & 0x20) {
			crc = (crc << 1) ^ CRC6_POLY;
			} else {
			crc <<= 1;
		}
	}
	return crc & 0x3F;
}

int main() {
	printf("const uint8_t crc6_table[64] = {\n    ");
		for (int i = 0; i < 64; i++) {
			printf("0x%02X%s", crc6_generate(i), (i % 8 == 7) ? ",\n    " : ", ");
		}
	printf("};\n");
	return 0;
}

*/
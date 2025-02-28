## Wiring Diagram
![Ekrano kopija 2025-02-28 200515](https://github.com/user-attachments/assets/bb35be41-aedc-4e5e-bf0c-5c564f190bd9)

* Red wire +5V
* Black wire GND
* Yellow wire CSN (MT6701 8 pin), Attiny1624 PA7 (5 pin)
* Green wire DO (MT6701 6 pin), Attiny1624 PB3 (6 pin)
* White wire CLK (MT6701 7 pin), Attiny1624 PB1 (8 pin)

The 470Ω resistor is an external pull-up for better signal quality, and it is optional.

## Firmware

The purpose of this firmware is to use USART0 as an SPI host, which allows preserving the EXCLK pin for future use. This means that, if needed, an external clock signal generator can be connected to the ATtiny1624 microcontroller.

The MT6701 SSI interface is identical to SPI, making USART0 a perfect fit.

The MT6701 data packet consists of:

* 14-bit ADC angle,
* 4 status bits,
* 6-bit CRC,
In other words, a total of 24 bits.

The firmware first verifies and separates the CRC. If the CRC is correct, **MT6701.CRCError = 0**. Then, the STATUS bits are extracted and divided into three categories:

* **MT6701.MagneticFieldStatus**
* **MT6701.PushButtonStatus**
* **MT6701.TrackStatus**
Finally, the angle is calculated: **MT6701.Angle**.

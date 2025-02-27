/*
 * CLK.c
 *
 * Created: 2025-02-27 17:58:36
 *  Author: Saulius
 */ 
 #include "Settings.h"

/**
 * @brief Initializes the internal high-frequency oscillator (OSCHF).
 * 
 * This function configures the ATTiny1614's internal oscillator to run at 20 MHz. 
 * It ensures proper configuration of the clock source and disables the prescaler for full-speed operation. 
 * Note: For SO14 packages, enabling clock output (CLKOUT) is not possible due to the absence of a dedicated pin.
 * 
 * @details
 * - Configures the clock source to use the 20 MHz internal oscillator (OSC20M).
 * - Disables the clock prescaler to achieve full-speed operation.
 * - Waits for the oscillator configuration to stabilize before exiting.
 */
void CLOCK_INHF_clock_init() {
    /* Enable the internal oscillator with a frequency of 20 MHz. */
    ccp_write_io((uint8_t *) &CLKCTRL.MCLKCTRLA, CLKCTRL_CLKSEL_OSC20M_gc /*| CLKCTRL_CLKOUT_bm*/); 
    // For SO14, it is impossible to enable CLKOUT due to the lack of a dedicated pin.

    /* Disable the main clock prescaler for full-speed operation. */
    ccp_write_io((uint8_t *) &CLKCTRL.MCLKCTRLB, CLKCTRL_PDIV_2X_gc & ~CLKCTRL_PEN_bm);

    /* Wait for the oscillator change to complete. */
    while (CLKCTRL.MCLKSTATUS & CLKCTRL_SOSC_bm) {};
}
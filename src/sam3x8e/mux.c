/*
 * mux.c
 *
 *  Created on: 25 okt 2014
 *      Author: Stefan
 */

#include "mux.h"
#include "pio.h"
#include "adc.h"

void enable_mux_pin(uint32_t mux, uint32_t pin) {
	pio_conf_pin(PIOC, 25, 0, 0);
	pio_conf_pin(PIOC, 26, 0, 0);
	pio_conf_pin(PIOC, 28, 0, 0);
	pio_conf_pin(PIOB, 25, 0, 0);

	pio_conf_pin(PIOB, 26, ((mux & 7) >> 2), 0);		// TODO: D26
	pio_conf_pin(PIOA, 15, ((mux & 3) >> 1), 0); 		// TODO: D24
	pio_conf_pin(PIOD, 1, (mux & 1), 0); 				// TODO: D22

	pio_set_pin(PIOC, 25, ((pin & 15) >> 3)); // S3
	pio_set_pin(PIOC, 26, ((pin & 7) >> 2)); // S2
	pio_set_pin(PIOC, 28, ((pin & 3) >> 1)); // S1
	pio_set_pin(PIOB, 25, (pin & 1)); // S0
}

//void disable_mux_pin(uint32_t mux, uint32_t pin) {
//	pio_conf_pin(PIOC, 25, 0, 0);
//	pio_conf_pin(PIOC, 26, 0, 0);
//	pio_conf_pin(PIOC, 28, 0, 0);
//	pio_conf_pin(PIOB, 25, 0, 0);
//
//	pio_conf_pin(PIOB, 26, ((mux & 7) >> 2), 0);		// TODO: D26
//	pio_conf_pin(PIOA, 15, ((mux & 3) >> 1), 0); 		// TODO: D24
//	pio_conf_pin(PIOD, 1, (mux & 1), 0); 				// TODO: D22
//
//	pio_set_pin(PIOC, 25, ((pin & 15) >> 3)); // S3
//	pio_set_pin(PIOC, 26, ((pin & 7) >> 2)); // S2
//	pio_set_pin(PIOC, 28, ((pin & 3) >> 1)); // S1
//	pio_set_pin(PIOB, 25, (pin & 1)); // S0
//}
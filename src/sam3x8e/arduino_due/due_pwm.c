/*
 * due_pwm.h
 * Pulse Width Modulation on Arduino Due
 *
 * Author: Andreas Drotth, Mattias Nilsson
 * Date: 29 October 2014
 */

#include "due_pwm.h"

void init_channel(uint32_t channel) {

	// Channel 6 - 9 is actual hardware (PWM) and has ID's over 21
	if (channel > PIN_PWML4_PC21_B){
		pwm_channel_setting_t channel_settings = {
		.channel = PWM_CHANNEL_0,
		.alignment = PWM_CHANNEL_ALIGN_LEFT,
		.polarity = PWM_CHANNEL_POLARITY_LOW,
		.duty_cycle = 0,
		.use_CLKx = 0,
		.frequency = 1000,
		.clock_ID = PWM_CLK_ID_CLKA
		}

		pwm_init_channel(channel_settings);
	}
	// The rest is PWM created with timers (TC)
	else {

	}
}

void set_duty_cycle(uint32_t channel, uint32_t duty) {
	if (channel > PIN_PWML4_PC21_B){

	}
	else {

	}
}

void enable_channel(uint32_t channel) {
	if (channel > PIN_PWML4_PC21_B){

	}
	else {

	}
}

void disable_channel(uint32_t channel) {
	if (channel > PIN_PWML4_PC21_B){

	}
	else {

	}
}

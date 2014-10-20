/*
 * tc.h
 * TC - Timer Counter
 * This API is used to control the three independent hardware timers.
 *
 * Author: Andreas Drotth, Mattias Nilsson
 * Date: 20 Oktober 2014
 */

#include "tc.h"

// TODO: make macro mask function, works for now but mask is better
void tc_conf_channel(tc_channel_settings_t* set, tc_reg_t *tc, uint32_t channel) {
	tc_channel_reg_t *tc_ch = tc->TC_CHANNEL + channel;

	//Common parameters
	tc_ch->TC_CMR = (set->tcclks << TC_CMR_TCCLKS_POS);
	tc_ch->TC_CMR |= (set->wave << TC_CMR_WAVE_POS);
//	tc->TC_CHANNEL[channel].TC_CMR |= (set->clki << 3);
//	tc->TC_CHANNEL[channel].TC_CMR |= (set->burst << 4);

	//Capture mode parameters
//	tc->TC_CHANNEL[channel].TC_CMR |= (set->ldbstop << );
//	tc->TC_CHANNEL[channel].TC_CMR |= (set->ldbdis << );
//	tc->TC_CHANNEL[channel].TC_CMR |= (set->etrgedg << );
//	tc->TC_CHANNEL[channel].TC_CMR |= (set->abetrg << );
//	tc->TC_CHANNEL[channel].TC_CMR |= (set->cpctrg << );
//	tc->TC_CHANNEL[channel].TC_CMR |= (set->ldra << );
//	tc->TC_CHANNEL[channel].TC_CMR |= (set->ldrb << );
//	tc->TC_CHANNEL[channel].TC_CMR |= (set->cpcstop << );
//	tc->TC_CHANNEL[channel].TC_CMR |= (set->cpcdis << );

}

void tc_conf_block(tc_block_settings_t* settings, tc_reg_t *tc){

}

void tc_enable_clock(tc_reg_t *tc, uint32_t channel) {
	if (channel > MAX_CHANNELS){
		return;
	}

	tc->TC_CHANNEL[channel].TC_CCR = TC_CCR_CLKEN;
}

void tc_disable_clock(tc_reg_t *tc, uint32_t channel){
	if (channel > MAX_CHANNELS){
		return;
	}
	tc->TC_CHANNEL[channel].TC_CCR = TC_CCR_CLKDIS;
}

void tc_start_clock(tc_reg_t *tc, uint32_t channel){
	if (channel > MAX_CHANNELS){
		return;
	}
	tc->TC_CHANNEL[channel].TC_CCR |= TC_CCR_SWTRG;
}

uint32_t tc_read_counter_value(tc_reg_t * tc, uint32_t channel){
	if (channel > MAX_CHANNELS){
		return 0;
	}
	return tc->TC_CHANNEL[channel].TC_CV;
}

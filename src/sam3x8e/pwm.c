/**
 * \class PWM
 * \brief Pulse Width Modulation (PWM)
 * \details This class is used to output a pulse width modulated waveform using
 * \details the PWM peripheral on the MCU.
 * \author Saeed Ghasemi
 * \version 0.1
 * \date 25 sep 2014
 * \pre
 * \bug
 */


#include "global_entities.h"
#include "pwm.h"

///\cond
// The first register in the Power Management Controller
uint32_t *const p_pwm_base_add = (uint32_t *) 0x40094000U;
/*
 *  Necessary registers addressed by incrementing the base address by an
 *  register-specific offset.
 */
#define PWM_CLK 	*(p_pwm_base_add + 0x000) // PWM Clock Register
#define PWM_ENA 	*(p_pwm_base_add + 0x004) // PWM Enable Register
#define PWM_DIS 	*(p_pwm_base_add + 0x008) // PWM Disable Register
#define PWM_SR 		*(p_pwm_base_add + 0x00C) // PWM Status Register
#define PWM_CMR 	*(p_pwm_base_add + 0x200) // PWM Channel Mode Register
#define PWM_CDTY 	*(p_pwm_base_add + 0x204) // PWM Channel Duty Cycle Register
#define PWM_CDTYUPD *(p_pwm_base_add + 0x208) // PWM Channel Duty Cycle Update Register
#define PWM_CPRD 	*(p_pwm_base_add + 0x20C) // PWM Channel Period Register
#define PWM_CPRDUPD *(p_pwm_base_add + 0x210) // PWM Channel Period Update Register


///\endcond

/**
 * Mask are being defined like this:
 * [PERIPHERAL]_[REGISTER]_[SECTION]_NR    (IF ANY NUMBER)
 */
#define PWM_CLK_PREA			(0x00000F00)
#define PWM_CLK_PREB			(0x0F000000)
#define PWM_CLK_DIVA			(0x000000FF)
#define PWM_CLK_DIVB			(0x00FF0000)

#define PWM_ENA_CHANNEL_0		0
#define PWM_ENA_CHANNEL_1		1
#define PWM_ENA_CHANNEL_2		2
#define PWM_ENA_CHANNEL_3		3
#define PWM_ENA_CHANNEL_4		4
#define PWM_ENA_CHANNEL_5		5
#define PWM_ENA_CHANNEL_6		6
#define PWM_ENA_CHANNEL_7		7

#define PWM_CMRx_CPRE			(0x0000000F)
#define PWM_CMRx_CALG			(1 << 8)
#define PWM_CMRx_CPOL			(1 << 9)
#define PWM_CMRx_CES			(1 << 10)
#define PWM_CMRx_DTE			(1 << 16)
#define PWM_CMRx_DTHI			(1 << 17)
#define PWM_CMRx_DTLI			(1 << 18)

#define PWM_CDTYx_CDTY			(0x0000FFFF)
#define PWM_CDTYUPDx_CDTYUPD	(0x0000FFFF)

#define PWM_CPRDx_CPRD			(0x0000FFFF)
#define PWM_CPRDUPDx_CPRDUPD	(0x0000FFFF)

//////////////////////////////////
/**
 * Parameters are being defined like this:
 * [PERIPHERAL]_[REGISTER]_[SECTION]_VALUE    (IF ANY NUMBER)
 */
//PESCALLERS FOR CLOCK REGISTER
#define PWM_CLK_PRES_1				(0b0000)
#define PWM_CLK_PRES_2				(0b0001)
#define PWM_CLK_PRES_4				(0b0010)
#define PWM_CLK_PRES_8				(0b0011)
#define PWM_CLK_PRES_16				(0b0100)
#define PWM_CLK_PRES_32				(0b0101)
#define PWM_CLK_PRES_64				(0b0110)
#define PWM_CLK_PRES_128			(0b0111)
#define PWM_CLK_PRES_256			(0b1000)
#define PWM_CLK_PRES_512			(0b1001)
#define PWM_CLK_PRES_1024			(0b1010)
//DIVIDERS FOR CLKA AND CLKB
#define PWM_CLK_DIVx_TURNOFF		0
#define PWM_CLK_DIVx_PREx			1
//PESCALLERS FOR CHANNEL MODE REGISTER
#define PWM_CMRx_PRES_1				(0b0000)
#define PWM_CMRx_PRES_2				(0b0001)
#define PWM_CMRx_PRES_4				(0b0010)
#define PWM_CMRx_PRES_8				(0b0011)
#define PWM_CMRx_PRES_16			(0b0100)
#define PWM_CMRx_PRES_32			(0b0101)
#define PWM_CMRx_PRES_64			(0b0110)
#define PWM_CMRx_PRES_128			(0b0111)
#define PWM_CMRx_PRES_256			(0b1000)
#define PWM_CMRx_PRES_512			(0b1001)
#define PWM_CMRx_PRES_1024			(0b1010)
#define PWM_CMRx_PRES_CLOCKA		(0b1011)
#define PWM_CMRx_PRES_CLOCKB		(0b1100)
// PARAMETERS FOR THE ALIGNMENT
#define PWM_CMRx_ALIGN_LEFT			0
#define PWM_CMRx_ALIGN_CENTER		1
// PARAMETERS FOR THE POLARITY
#define PWM_CMRx_POLARITY_HIGH		1
#define PWM_CMRx_POLARITY_LOW		0
//////////////////////////////////



void function(){

}





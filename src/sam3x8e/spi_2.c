/**
 * @file pwm.c
 * @brief Pulse Width Modulation (PWM)
 * @details An API for controlling the PWM peripheral inside a SAM3X8E MCU.
 * This peripheral is an embedded macrocell within the MCU and all of its 44
 * registers are physically mapped on this macrocell, therefore modifying the
 * register requires that the peripheral clock is enabled in PMC. However, when
 * modified, the register values are stored even it the peripheral clock is
 * turned off and the peripheral will continue its operation when the clock is
 * turned back on.
 * This API implements all 8 independent channels and their change of polarity,
 * alignment, PWM frequency and handles the pin multiplexing for all 16 outputs
 * of the peripheral. The API does not stop any clock once it has started them.
 * @author Saeed Ghasemi
 * @date 28 sep 2014
 * @pre The API handles all of its dependencies on other peripherals
 * internally and will start other clocks in order to properly operate.
 * @bug Manually tested all functions to comply with all demands.
 * The only problem is that the register set defined below is not working when
 * implemented. The register mapping currently working is non conventional.
 */

#include "spi_2.h"

uint8_t spi_init(spi_reg_t *spi, const spi_settings_t *settings) {
	// These settings are not implemented in this API and are therefore
	// hardcoded to the following:
	// -> set master
	// -> set to fixed peripheral select
	// -> chip select decode 'off'
	// -> mode fault detection 'off'
	// -> Wait Data Read Before Transfer 'off' (send data at any time)

	// TODO set:
	// Peripheral Chip Select to none
	// Delay Between Chip Selects to

	return 1;
}

uint8_t spi_init_selector(spi_reg_t *spi,
		const spi_selector_settings_t *settings);

uint8_t spi_set_master(spi_reg_t *spi);

uint8_t spi_set_slave(spi_reg_t *spi);

uint8_t spi_selector_set_clk_polarity(spi_reg_t *spi, uint8_t selector,
		uint8_t polarity);

uint8_t spi_selector_set_clk_phase(spi_reg_t *spi, uint8_t selector,
		uint8_t phase);

uint8_t spi_selector_set_baud_rate(spi_reg_t *spi, uint8_t selector,
		uint8_t baud_rate) {
	uint32_t *p_reg;
	// Boundary test. Higher than these values will result in error or
	// register corruption, because the selector is used to calculate a
	// pointer.
	if (baud_rate > 255 || selector > 3) {
		return 0; // Error
	}
	// Calculate the pointer for the selector based on the first
	// selector register being the offset.
	p_reg = (&spi->SPI_CSR0) + selector; // pointer increment of 0 to 3.
	// Bitwise operation to set the delay for the calculated register to use
	*p_reg = ((~SPI_CSRx_SCBR_MASK) & *p_reg) | (baud_rate << 8);
	return 1; // No error
}

uint8_t spi_selector_do_not_keep_cs_active(spi_reg_t *spi, uint8_t selector,
		uint8_t option) {
	uint32_t *p_reg;
	// Boundary test. Higher than these values will result in error or
	// register corruption, because the selector is used to calculate a
	// pointer.
	if (option > 1 || selector > 3) {
		return 0; // Error
	}
	// Calculate the pointer for the selector based on the first
	// selector register being the offset.
	p_reg = (&spi->SPI_CSR0) + selector; // pointer increment of 0 to 3.
	// Bitwise operation to set the delay for the calculated register to use
	*p_reg = ((~SPI_CSRx_CSNAAT_MASK) & *p_reg) | (option << 2);
	return 1; // No error
}

uint8_t spi_selector_keep_cs_active(spi_reg_t *spi, uint8_t selector,
		uint8_t option) {
	uint32_t *p_reg;
	// Boundary test. Higher than these values will result in error or
	// register corruption, because the selector is used to calculate a
	// pointer.
	if (option > 1 || selector > 3) {
		return 0; // Error
	}
	// Calculate the pointer for the selector based on the first
	// selector register being the offset.
	p_reg = (&spi->SPI_CSR0) + selector; // pointer increment of 0 to 3.
	// Bitwise operation to set the delay for the calculated register to use
	*p_reg = ((~SPI_CSRx_CSAAT_MASK) & *p_reg) | (option << 3);
	return 1; // No error
}

uint8_t spi_selector_set_bit_length(spi_reg_t *spi, uint8_t selector,
		uint8_t bit_count) {
	uint32_t *p_reg;
	// Boundary test. Higher than these values will result in error or
	// register corruption, because the selector is used to calculate a
	// pointer.
	if ((bit_count > 8) || (selector > 3)) {
		return 0; // Error
	}
	// Calculate the pointer for the selector based on the first
	// selector register being the offset.
	p_reg = (&spi->SPI_CSR0) + selector; // pointer increment of 0 to 3.
	// Bitwise operation to set the delay for the calculated register to use
	*p_reg = ((~SPI_CSRx_BITS_MASK) & *p_reg) | (bit_count << 4);
	return 1; // No error
}

uint8_t spi_selector_set_delay_between_cs(spi_reg_t *spi, uint8_t selector,
		uint8_t delay) {
	uint32_t *p_reg;
	uint8_t divisor;
	// Boundary test. Higher than these values will result in error or
	// register corruption, because the selector is used to calculate a
	// pointer.
	// If the value is below 12 ns, it's OK. The MCU will adjust it itself to
	// the minimum value of 12 ns.
	if (delay > 3036 || selector > 3) {
		return 0; // Error
	}
	// Calculate the pointer for the selector based on the first
	// selector register being the offset.
	p_reg = (&spi->SPI_CSR0) + selector; // pointer increment of 0 to 3.
	// Calculate the divisor having though of round-downs with integers
	divisor = (uint8_t) ((delay * 84U) / 1000U);
	// Bitwise operation to set the delay for the calculated register to use
	*p_reg = ((~SPI_MR_DLYBCS_MASK) & *p_reg) | (divisor << 24);
	return 1; // No error
}

uint8_t spi_selector_set_delay_clk_start(spi_reg_t *spi, uint8_t selector,
		uint8_t delay) {
	uint32_t *p_reg;
	uint8_t divisor;
	// Boundary test. Higher than these values will result in error or
	// register corruption, because the selector is used to calculate a
	// pointer.
	if (delay > 3036 || selector > 3) {
		return 0; // Error
	}
	// Calculate the pointer for the selector based on the first
	// selector register being the offset.
	p_reg = (&spi->SPI_CSR0) + selector; // pointer increment of 0 to 3.
	// Calculate the divisor having though of round-downs with integers
	divisor = (uint8_t) ((delay * 84U) / 1000U);
	// Bitwise operation to set the delay for the calculated register to use
	*p_reg = ((~SPI_CSRx_DLYBS_MASK) & *p_reg) | (divisor << 16);
	return 1; // No error
}

uint8_t spi_selector_set_delay_delay_transfers(spi_reg_t *spi, uint8_t selector,
		uint32_t delay) {
	uint32_t *p_reg;
	uint8_t divisor;
	// Boundary test. Higher than these values will result in error or
	// register corruption, because the selector is used to calculate a
	// pointer.
	if (delay > 97143 || selector > 3) {
		return 0; // Error
	}
	// Calculate the pointer for the selector based on the first
	// selector register being the offset.
	p_reg = (&spi->SPI_CSR0) + selector; // pointer increment of 0 to 3.
	// Calculate the divisor having though of round-downs with integers
	divisor = (uint8_t) ((delay * 84U) / 32U) / 1000U;
	// Bitwise operation to set the delay for the calculated register to use
	*p_reg = ((~SPI_CSRx_DLYBCT_MASK) & *p_reg) | (divisor << 24);
	return 1; // No error
}

uint8_t spi_loopback_enable(spi_reg_t *spi);

uint8_t spi_loopback_disable(spi_reg_t *spi);

uint8_t spi_enable(spi_reg_t *spi);

uint8_t spi_disable(spi_reg_t *spi);

uint8_t spi_select_slave(spi_reg_t *spi, uint8_t slave) {
	// TODO use bitwise operation
	spi->SPI_MR &= ~(0b1111 << 16);	//clear bit 16 to 19 in SPI_MR
	spi->SPI_MR |= (0b111u >> (uint32_t) (3 - slave)) << 16; //set bit 16 to 18 in SPI_MR (could be predefined)
	return 1;
}

uint8_t spi_tx_ready(spi_reg_t *spi);

uint8_t spi_rx_ready(spi_reg_t *spi);

uint8_t spi_master_write(spi_reg_t *spi, uint16_t data){
	// transfer begins when processor writes to spi->SPI_TDR
	// before writing SPI_TDR, PCS field in SPI_MR must be set in order to select slave

	//if SPI_RDR has not been read OVRES in SPI_SR is set
	//user has to read SPI_SR to clear OVRES

	// Retrieving the register and modifying it (Storing error output in shift)
	spi->SPI_TDR = (spi->SPI_TDR & 0xFFFF0000) | data;
}

uint8_t spi_transmission_done(spi_reg_t *spi);

uint16_t spi_read(spi_reg_t *spi, uint16_t dummy_data);

uint8_t spi_slave_write(spi_reg_t *spi, uint16_t data);

uint8_t spi_software_reset(spi_reg_t *spi);

uint8_t spi_selector_close(void);


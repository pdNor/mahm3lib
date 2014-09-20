/*!
 * \brief brief description
 * \details detailed description
 *
 * \author Theodor Lindquist
 * \author Soded Alatia
 *
 * \version 0.2
 * \date Sep 18, 2014
 *
 * \pre requirements
 */

#ifndef TEST_PIO_H_
#define TEST_PIO_H_

#include <stdint.h>

uint8_t test_pio_pullup(void);	//testing pio_conf_*
uint8_t test_pio_output(void);	//testing pio_conf_*
uint8_t test_pio_read_pin(void);	//testing pio_read_*
uint8_t test_pio_set_output(void);	//testing pio_set_*

#endif /* TEST_PIO_H_ */

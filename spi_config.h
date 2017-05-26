/*
 * spi_config.h
 *
 *  Created on: May 25, 2017
 *      Author: evan
 */

#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

#include "csl_spi.h"

#define SPI_MIDI_CMD 0x01
#define SPI_ENC_CMD  0x02
#define SPI_POT_CMD  0x03
#define SPI_SWT_CMD  0x04


extern CSL_SpiHandle	hSpi;
extern SPI_Config		spi_hwConfig;

void spi_init( void );
void spi_write( Uint16 *write_buf, Uint16 buf_len );
void spi_read( Uint16 *read_buf, Uint16 buf_len );


#endif /* SPI_CONFIG_H_ */

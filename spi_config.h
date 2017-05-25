/*
 * spi_config.h
 *
 *  Created on: May 25, 2017
 *      Author: evan
 */

#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

#include "csl_spi.h"

extern CSL_SpiHandle	hSpi;

void spi_init( void );
void spi_write( Uint16 *write_buf, Uint16 buf_len );
void spi_read( Uint16 *read_buf, Uint16 buf_len );


#endif /* SPI_CONFIG_H_ */

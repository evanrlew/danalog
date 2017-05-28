/*
 * i2s_dma.h
 *
 *  Created on: May 8, 2017
 *      Author: evan
 */



#ifndef I2S_DMA_H_
#define I2S_DMA_H_

#include "csl_dma.h"

#define I2S_DMA_BUFFER_SIZE 128

extern Int16 left_ping[I2S_DMA_BUFFER_SIZE];
extern Int16 left_pong[I2S_DMA_BUFFER_SIZE];

extern Int16 right_ping[I2S_DMA_BUFFER_SIZE];
extern Int16 right_pong[I2S_DMA_BUFFER_SIZE];


void i2s_dma_init( void );
void dma_isr(void);

#endif /* I2S_DMA_H_ */
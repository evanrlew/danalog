/*
 * i2s_dma.h
 *
 *  Created on: May 8, 2017
 *      Author: evan
 */



#ifndef I2S_DMA_H_
#define I2S_DMA_H_

#define I2S_DMA_BUFFER_SIZE 128

extern Int16 dmaPingSrcBuf[I2S_DMA_BUFFER_SIZE];
extern Int16 dmaPongSrcBuf[I2S_DMA_BUFFER_SIZE];


void i2s_dma_init( void );
interrupt void DmaIsr(void);

#endif /* I2S_DMA_H_ */

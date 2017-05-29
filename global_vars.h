/*
 * global_vars.h
 *
 *  Created on: May 25, 2017
 *      Author: evan
 */

#ifndef GLOBAL_VARS_H_
#define GLOBAL_VARS_H_

#include "ezdsp5535.h"
#include "io/midi_queue.h"

// SPI recieving data structures
extern Uint16 encoders[19];
extern Uint16 pots[8];
extern Uint16 switches;
extern Uint16 midi[3];

// I2S/DMA buffers for audio output
#define I2S_DMA_BUFFER_SIZE 128
extern Int16 left_ping[I2S_DMA_BUFFER_SIZE];
extern Int16 left_pong[I2S_DMA_BUFFER_SIZE];

extern Int16 right_ping[I2S_DMA_BUFFER_SIZE];
extern Int16 right_pong[I2S_DMA_BUFFER_SIZE];

// Midi buffer
extern MidiPacket midi_buffer[];



#endif /* GLOBAL_VARS_H_ */

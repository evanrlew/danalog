/*
 * midi_queue.h
 *
 *  Created on: May 28, 2017
 *      Author: evan
 */

#ifndef MIDI_QUEUE_H_
#define MIDI_QUEUE_H_

#include "ezdsp5535.h"
#include "midi.h"

#define MIDI_BUFFER_SIZE 16

extern Uint16 writeLoc, readLoc;

void midi_buffer_init();
void midi_buffer_write( MidiPacket p );
MidiPacket midi_buffer_read( void );
Uint16 midi_buffer_size( void );

#endif /* MIDI_QUEUE_H_ */

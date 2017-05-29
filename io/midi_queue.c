/*
 * midi_queue.c
 *
 *  Created on: May 28, 2017
 *      Author: evan
 */
#include "midi_queue.h"
#include "../global_vars.h"

Uint16 writeLoc, readLoc;
MidiPacket midi_buffer[MIDI_BUFFER_SIZE];

void midi_buffer_init()
{
	writeLoc = 0;
	readLoc  = 0;
}

void midi_buffer_write( MidiPacket p )
{
	midi_buffer[writeLoc] = p;
	writeLoc = (writeLoc + 1) % MIDI_BUFFER_SIZE;
}

MidiPacket midi_buffer_read( void )
{
	if (midi_buffer_size() == 0) {
		while (1); // tried to read from empty buffer
	}

	MidiPacket p = midi_buffer[readLoc];
	readLoc = (readLoc + 1) % MIDI_BUFFER_SIZE;
	return p;
}

Uint16 midi_buffer_size( void )
{
	return (writeLoc - readLoc + MIDI_BUFFER_SIZE) % MIDI_BUFFER_SIZE;
}



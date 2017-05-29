/*
 * midi_queue.h
 *
 *  Created on: May 28, 2017
 *      Author: evan
 */

#ifndef MIDI_QUEUE_H_
#define MIDI_QUEUE_H_

#include "ezdsp5535.h"

#define MIDI_BUFFER_SIZE 16

enum midi_cmd_type {
	MIDI_NOTE_ON,
	MIDI_NOTE_OFF
};

typedef enum midi_cmd_type MidiCommand;

struct midi_packet_struct {
	Uint16 midi_cmd;
	Uint16 note_id;
	Uint16 velocity;
};
typedef struct midi_packet_struct MidiPacket;

void midi_buffer_init();
void midi_buffer_write( MidiPacket p );
MidiPacket midi_buffer_read( void );
Uint16 midi_buffer_size( void );

#endif /* MIDI_QUEUE_H_ */

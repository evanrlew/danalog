/*
 * midi_utils.h
 *
 *  Created on: May 29, 2017
 *      Author: evan
 */

#ifndef MIDI_UTILS_H_
#define MIDI_UTILS_H_

#include <std.h>

enum midi_cmd_type {
	MIDI_NOTE_ON,
	MIDI_NOTE_OFF,
	MIDI_UNKNOWN
};

typedef enum midi_cmd_type MidiCommand;


struct midi_packet_struct {
	Uint16 midi_cmd;
	Uint16 note_id;
	Uint16 velocity;
};
typedef struct midi_packet_struct MidiPacket;

MidiCommand midi_packet_type(MidiPacket);


Int16 convert_to_freq(Uint16 midi_note);


#endif /* MIDI_UTILS_H_ */

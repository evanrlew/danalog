/*
 * gen_sound.h
 *
 *  Created on: May 6, 2017
 *      Author: evan
 */

#ifndef GEN_SOUND_H_
#define GEN_SOUND_H_

#include <std.h>

#include "../io/midi.h"

typedef enum {
	ENV_ATTACK, ENV_DECAY, ENV_SUSTAIN, ENV_RELEASE
} EnvelopeState;


typedef struct {
	Uint16 pitch;
	Uint16 velocity;
	EnvelopeState mod_env_state;
	EnvelopeState car_env_state;
	Uint16 mod_env_counter;
	Uint16 car_env_counter;

} FMNote;

FMNote midi_to_fm_note(MidiPacket* p);

#endif /* GEN_SOUND_H_ */

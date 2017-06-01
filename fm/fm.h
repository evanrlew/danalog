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
#include "envelope.h"
#include "../audio/singen.h"


typedef struct {
	Int16 pitch;
	Int16 velocity;
	Envelope mod_env;
	Envelope car_env;
	SinState mod_sin;
	SinState car_sin;


} FMNote;

FMNote midi_to_fm_note(MidiPacket* p);





#endif /* GEN_SOUND_H_ */

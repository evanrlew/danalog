/*
 * gen_sound.c
 *
 *  Created on: May 6, 2017
 *      Author: evan
 */

#include "fm.h"

/* Standard C includes */
#include <std.h>
#include <tsk.h>

/* DSP/BIOS headers */
#include "hellocfg.h"

/* ezDSP C5535 board specific headers */
#include "ezdsp5535.h"

/* Danalog headers */
#include "../audio/singen.h"
#include "../audio/sintable.h"
#include "../global_vars.h"
#include "../io/midi.h"

FMNote note;
SinState ss_carrier, ss_mod;

FMNote midi_to_fm_note(MidiPacket* p) {
	FMNote n;
	n.pitch = convert_to_freq(p->note_id);
	n.velocity = (Int16) p->velocity;
	n.mod_env_state = ENV_ATTACK;
	n.mod_env = 1;
	n.car_env_state = ENV_ATTACK;
	n.car_env = 1;
	return n;
}


Void generate_samples_tsk( Void )
{

	Int16 mod_ratio = 1;
	Int16 mod_depth = 1;




	while (1) {
		SEM_pend(&ping_pong_sem, SYS_FOREVER);
		MidiPacket p;
		while (midi_buffer_size() > 0) {
			p = midi_buffer_read();
		}


		if (midi_packet_type(p) == MIDI_NOTE_ON) {
			note = midi_to_fm_note(&p);
			if (note.pitch != ss_carrier.frequency) {
				sin_compute_params(&ss_carrier, note.pitch);
				sin_compute_params(&ss_mod,  note.pitch * mod_ratio);
			}

		}
		else {
			note.car_env_state = ENV_RELEASE;
			note.mod_env_state = ENV_RELEASE;
			note.car_env = 0;
			note.mod_env = 0;
		}

		// determine which buffer to fill
		Int16 *left_output, *right_output;
		if (CSL_DMA1_REGS->DMACH0TCR2 & 0x0002) { // last xfer: pong
			left_output = left_pong;
			right_output = right_pong;
		} else {
			left_output = left_ping;
			right_output = right_ping;
		}

		Int16 i;
#pragma MUST_ITERATE(I2S_DMA_BUFFER_SIZE,I2S_DMA_BUFFER_SIZE)
		for (i = 0; i < I2S_DMA_BUFFER_SIZE; i++) {
			Int16 mod = note.mod_env * sin_gen(&ss_mod, 0);
			//Int16 mod_scaled = (mod_depth * mod * SINTABLE_LENGTH * 4) / ( 205887 );
			Int16 mod_scaled = (mod >> 3) * mod_depth;

			Int16 output = note.car_env * sin_gen(&ss_carrier, mod_scaled);// >> 6;
			left_output[i] = output;
			right_output[i] = output;
		} // end for
	} // end while (1)
}

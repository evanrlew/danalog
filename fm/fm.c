/*
 * gen_sound.c
 *
 *  Created on: May 6, 2017
 *      Author: evan
 */

#include "fm.h"

/* Standard C includes */
#include <std.h>
#include <stdio.h>
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
#include "envelope.h"

SinState ss_carrier, ss_mod;

EnvelopeConfig mod_env_cfg, car_env_cfg;

FMNote note;



FMNote midi_to_fm_note(MidiPacket* p) {
	FMNote n;
	n.pitch = convert_to_freq(p->note_id);
	n.velocity = (Int16) p->velocity;
	n.car_env = createEnvelope(&car_env_cfg);
	n.mod_env = createEnvelope(&mod_env_cfg);
	return n;
}


Void generate_samples_tsk( Void )
{

	Int16 mod_ratio = 1;
	Int16 mod_depth = 1;

	createEnvelopeConfig(&car_env_cfg, 20, 20, 250, 100);
	createEnvelopeConfig(&mod_env_cfg, 200, 100, 100, 100);

	while (1) {
		SEM_pend(&ping_pong_sem, SYS_FOREVER);

		MidiPacket p;
		if (midi_buffer_size() > 0) {
			while (midi_buffer_size() > 0) {
				p = midi_buffer_read();
			}

			if (midi_packet_type(p) == MIDI_NOTE_ON) {
				note = midi_to_fm_note(&p);
				sin_compute_params(&ss_carrier, note.pitch);
				sin_compute_params(&ss_mod,  note.pitch * mod_ratio);
			}
			else if (midi_packet_type(p) == MIDI_NOTE_OFF) { // MIDI_NOTE_OFF
				note.car_env.env_state = ENV_RELEASE;
				note.mod_env.env_state = ENV_RELEASE;
			}
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
			Int32 mod = (envelopeIncrement(&note.mod_env) * (Int32) sin_gen(&ss_mod, 0)) / 256;
			//Int16 mod_scaled = (mod_depth * mod * SINTABLE_LENGTH * 4) / ( 205887 );
			Int32 mod_scaled = (mod >> 3) * mod_depth;

			Int16 output = (envelopeIncrement(&note.car_env) * (Int32) sin_gen(&ss_carrier, mod_scaled)) / 256;// >> 6;
			left_output[i] = output;
			right_output[i] = output;
		} // end for
	} // end while (1)
}

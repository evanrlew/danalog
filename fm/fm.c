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
#include "ringbuf.h"

EnvelopeConfig mod_env_cfg, car_env_cfg;

FMNote note;


Int16 mod_ratio = 1;
Int16 mod_depth = 5;


FMNote midi_to_fm_note(MidiPacket* p) {
	FMNote n;
	n.pitch = convert_to_freq(p->note_id);
	n.velocity = (Int16) p->velocity;
	n.mod_env = createEnvelope(&mod_env_cfg);
	n.car_env = createEnvelope(&car_env_cfg);
	sin_compute_params(&n.mod_sin, n.pitch * mod_ratio);
	sin_compute_params(&n.car_sin, n.pitch);
	return n;
}


Void generate_samples_tsk( Void )
{



	createEnvelopeConfig(&car_env_cfg, 0, 0, 250, 100);
	createEnvelopeConfig(&mod_env_cfg, 1, 10, 100, 100);

	while (1) {
		SEM_pend(&ping_pong_sem, SYS_FOREVER);
		//createEnvelopeConfig(&car_env_cfg, encoders[10], encoders[11], encoders[12], encoders[13]);
		//createEnvelopeConfig(&mod_env_cfg, encoders[14], encoders[15], encoders[16], encoders[17]);

		MidiPacket p;
		if (midi_buffer_size() > 0) {
			while (midi_buffer_size() > 0) {
				p = midi_buffer_read();

				if (midi_packet_type(p) == MIDI_NOTE_ON) {
					add_note(&p, mod_ratio);
				}
				else if (midi_packet_type(p) == MIDI_NOTE_OFF) { // MIDI_NOTE_OFF
					release_note(&p);
				}
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
			Int16 output = 0;
			Int16 counter;
#pragma MUST_ITERATE(NOTE_BUF_LEN,NOTE_BUF_LEN)
			for (counter = 0; counter < NOTE_BUF_LEN; counter++) {
				FMNote *n = &note_buf[counter];
				if (n->car_env.env_state != ENV_INACTIVE) {
					Int32 mod = ((envelopeIncrement(&n->mod_env) * (Int32) sin_gen(&n->mod_sin, 0))) >> 8;
					Int32 mod_scaled = (mod >> 3) * mod_depth;

					output += ((envelopeIncrement(&n->car_env) * (Int32) sin_gen(&n->car_sin, mod_scaled))) >> 10;
				}
			}

			left_output[i] = output;
			right_output[i] = output;
		} // end for
	} // end while (1)
}

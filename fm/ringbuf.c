/*
 * ringbuf.c
 *
 *  Created on: May 31, 2017
 *      Author: evan
 */
#include "ringbuf.h"

Int16 note_buf_head = 0;
FMNote note_buf[NOTE_BUF_LEN];

void add_note(MidiPacket *p, Int16 mod_ratio) {
	FMNote *n = &note_buf[note_buf_head];
	*n = midi_to_fm_note(p);

	sin_compute_params(&n->mod_sin, n->pitch * mod_ratio);
	sin_compute_params(&n->car_sin,  n->pitch);

	note_buf_head = (note_buf_head + 1) % NOTE_BUF_LEN;
}

void release_note(MidiPacket *p) {
	Int16 i;
	for (i = 0; i < NOTE_BUF_LEN; i++) {
		FMNote *n = &note_buf[i];
		if (n->pitch == convert_to_freq(p->note_id)) {
			n->car_env.env_state = ENV_RELEASE;
			n->mod_env.env_state = ENV_RELEASE;
		}
	}
}

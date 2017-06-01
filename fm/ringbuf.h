/*
 * ringbuf.h
 *
 *  Created on: May 31, 2017
 *      Author: evan
 */

#ifndef RINGBUF_H_
#define RINGBUF_H_

#include "fm.h"
#include "../io/midi.h"

#define NOTE_BUF_LEN 2

extern FMNote note_buf[NOTE_BUF_LEN];

void add_note(MidiPacket *p, Int16 mod_ratio);
void release_note(MidiPacket *p);


#endif /* RINGBUF_H_ */

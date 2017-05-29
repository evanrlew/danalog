/*
 * midi.c
 *
 *  Created on: May 29, 2017
 *      Author: evan
 */
#include "midi.h"

MidiCommand midi_packet_type(MidiPacket p)
{
	if (p.midi_cmd == 0x90) {
		return MIDI_NOTE_ON;
	}
	else if (p.midi_cmd == 0x80) {
		return MIDI_NOTE_OFF;
	}
	else {
		return MIDI_UNKNOWN;
	}
}

Uint16 midi_freq[88] = {
		28,29,31,33,35,37,39,41,44,46,49,52,55,58,62,65,69,73,78,82,
		87,93,98,104,110,117,124,131,139,147,156,165,175,185,196,208,
		220,233,247,262,277,294,311,330,349,370,392,415,440,466,494,523,
		554,587,622,659,699,740,784,831,880,932,988,1047,1109,1175,1245,
		1319,1397,1480,1568,1661,1760,1865,1976,2093,2218,2349,2489,2637,
		2794,2960,3136,3322,3520,3729,3951,4186
};

Uint16 convert_to_freq(Uint16 midi_note) {
	return midi_freq[midi_note - 21];
}


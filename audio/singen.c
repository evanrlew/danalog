#include "singen.h"

#include "sintable.h"
#include "stdio.h"



void sin_compute_params(SinState *state, Int32 frequency) {
	state->frequency = frequency;
	state->step_delta = (frequency * 8192) / SAMPLE_RATE;
	state->position = 0;
}

Int16 _decompress_sin(Int16 index) {
	if (index > 8192|| index < 0) {
//		printf("ERROR: Index out of range. index = %d", index);
		while(1);
	}

//	if (index < SINTABLE_LENGTH) {
//		return sintable[index];
//	}
//	else if (index < SINTABLE_LENGTH * 2) {
//		index = SINTABLE_LENGTH - (index - SINTABLE_LENGTH) - 1;
//		return sintable[index];
//	}
//	else if (index < SINTABLE_LENGTH * 3) {
//		index = index - 4096;
//		return _sneg(sintable[index]);
//	}
//	else {
//		index = SINTABLE_LENGTH - (index - SINTABLE_LENGTH) - 1;
//		return _sneg(sintable[index]);
//	}

	Int16 multiplier = 1;
	if (index >= 4096) {
		multiplier = -1;
		index = index - 4096;
	}

	if (index >= SINTABLE_LENGTH) { // reflect 3999->2000 to 1999->0
		index = SINTABLE_LENGTH - (index - SINTABLE_LENGTH) - 1;
	}

	return sintable[index] * multiplier;


}

Int16 sin_gen(SinState *state, Int16 mod) {
	Int16 position_mod;
	state->position = (state->step_delta + state->position) & 8191;
	position_mod = (state->position + mod) & 8191;
	return _decompress_sin(position_mod);
}

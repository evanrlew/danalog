#include "singen.h"

#include "sintable.h"
#include "stdio.h"

extern const Int16 sintable[];
Int16 position_mod;

Int16 _decompress_sin(Int16 index) {
	if (index > 8192|| index < 0) {
		printf("ERROR: Index out of range. index = %d", index);
	}

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

	state->position = (state->step_delta + state->position) % 8192;
	position_mod = positive_mod((state->position + mod), 8192);
	return _decompress_sin(position_mod);
}

void sin_compute_params(SinState *state, Int32 frequency) {
	state->frequency = frequency;
	state->step_delta = (frequency * 8192) / SAMPLE_RATE;
	state->position = 0;
}

Int16 positive_mod(Int16 i, Int16 n) {
	return (i % n + n) % n;
}

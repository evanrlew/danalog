#include "singen.h"

#include "sintable.h"
#include "stdio.h"



void sin_compute_params(SinState *state, Int32 frequency) {
	state->frequency = frequency;
	state->step_delta = (frequency * 8192) / SAMPLE_RATE;
	state->position = 0;
}



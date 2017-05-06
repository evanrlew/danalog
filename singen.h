/*
 * singen.h
 *
 *  Created on: May 2, 2017
 *      Author: evan
 */

#ifndef SINGEN_H_
#define SINGEN_H_

#include "ezdsp5535.h"

#define SAMPLE_RATE 48000

struct sin_state {
	Int32 position;
	Int32 frequency;
	Int32 step_delta;

};
typedef struct sin_state SinState;

Int16 _decompress_sin(Int16 index);
Int16 sin_gen(SinState *state, Int16 mod);
void sin_compute_params(SinState *state, Int32 frequency);
Int16 positive_mod(Int16 i, Int16 n);





#endif /* SINGEN_H_ */

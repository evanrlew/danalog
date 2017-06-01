/*
 * envlope.h
 *
 *  Created on: May 29, 2017
 *      Author: evan
 */

#ifndef ENVLOPE_H_
#define ENVLOPE_H_

#include <std.h>

typedef enum {
	ENV_ATTACK, ENV_DECAY, ENV_SUSTAIN, ENV_RELEASE, ENV_INACTIVE
} EnvelopeState;



typedef struct {
	Int16 attack;
	Int16 attack_step_cnt;

	Int16 decay;
	Int16 decay_step_cnt;

	Int16 sustain;

	Int16 release;
	Int16 release_step_cnt;

} EnvelopeConfig;

typedef struct {
	EnvelopeConfig *env_config;
	// State variables
	EnvelopeState env_state;
	Int16 env_val;
	Int16 step_cnt;
} Envelope;

void createEnvelopeConfig(EnvelopeConfig *ec, Int16 a, Int16 d, Int16 s, Int16 r) ;
Envelope createEnvelope(EnvelopeConfig *ec);
Int16 envelopeIncrement(Envelope *e);



#endif /* ENVLOPE_H_ */

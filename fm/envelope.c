/*
 * envelope.c
 *
 *  Created on: May 29, 2017
 *      Author: evan
 */
#include "envelope.h"

void createEnvelopeConfig(EnvelopeConfig *ec, Int16 a, Int16 d, Int16 s, Int16 r) {
	ec->attack = a;
	ec->decay = d;
	ec->sustain = s;
	ec->release = r;

	ec->attack_step_cnt = a * 4;
	ec->decay_step_cnt = d * 4;
	ec->release_step_cnt = r * 4;
}

Envelope createEnvelope(EnvelopeConfig *ec) {
	Envelope e;
	e.env_config = ec;
	e.env_state = ENV_ATTACK;
	e.env_val = 0;
	e.step_cnt = 0;
	return e;
}
Int16 envelopeIncrement(Envelope *e) {
	if (e->env_state == ENV_ATTACK) {
		if (e->env_val <= 255) {
			if (e->step_cnt < e->env_config->attack_step_cnt) {
				e->step_cnt++;
			} else {
				e->step_cnt = 0;
				e->env_val++;
			}
		} else {
			e->env_state = ENV_DECAY;
			e->step_cnt = 0;
		}
	}
	else if (e->env_state == ENV_DECAY) {
		if (e->env_val > e->env_config->sustain) {
			if (e->step_cnt < e->env_config->decay_step_cnt) {
				e->step_cnt++;
			} else {
				e->step_cnt = 0;
				e->env_val--;
			}
		} else {
			e->env_state = ENV_SUSTAIN;
			e->env_val = e->env_config->sustain;
		}
	} else if (e->env_state == ENV_RELEASE) {
		if (e->env_val > 0) {
			if (e->step_cnt < e->env_config->release_step_cnt) {
				e->step_cnt++;
			} else {
				e->step_cnt = 0;
				e->env_val--;
			}
		} else {
			return 0;
		}
	}
	return e->env_val;
}




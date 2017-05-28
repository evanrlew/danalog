/*
 * gen_sound.c
 *
 *  Created on: May 6, 2017
 *      Author: evan
 */

#include "gen_sound.h"

#include <std.h>
#include <tsk.h>

#include <stdio.h>

#include "hellocfg.h"

#include "ezdsp5535.h"
#include "ezdsp5535_i2s.h"
#include "ezdsp5535_i2c.h"
#include "csl_i2s.h"

#include "../audio/singen.h"
#include "../audio/sintable.h"

#include "../drivers/i2s_dma.h"

extern CSL_I2sHandle   hI2s;


Void generate_samples_tsk( Void )
{
	Int16 freq = 100;
	Int16 mod_ratio = 1;
	Int16 mod_depth = 5;

	SinState ss_carrier;
	sin_compute_params(&ss_carrier, freq);

	SinState ss_mod;
	sin_compute_params(&ss_mod, freq * mod_ratio);


	while (1) {
		SEM_pend(&ping_pong_sem, SYS_FOREVER);

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
			Int16 mod = sin_gen(&ss_mod, 0);
			//mod_scaled = (mod_depth * mod * SINTABLE_LENGTH * 4) / ( 205887 );
			Int16 mod_scaled = (mod >> 3) * mod_depth;

			Int16 output = sin_gen(&ss_carrier, mod_scaled);// >> 6;
			left_output[i] = output;
			right_output[i] = output;
		} // end for
	} // end while (1)
}

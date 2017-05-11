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

#include "aic3204.h"
#include "singen.h"
#include "sintable.h"

#include "i2s_dma.h"

extern CSL_I2sHandle   hI2s;


Void gen_sound_tsk( Void )
{
	Int16 freq = 500;
	Int16 mod_ratio = 1;
	Int16 mod_depth = 5;

	SinState ss_carrier;
	sin_compute_params(&ss_carrier, freq);

	SinState ss_mod;
	sin_compute_params(&ss_mod, freq * mod_ratio);



	Int16 output, mod_scaled;
	Int32 mod;
//	ioport  CSL_I2sRegs   *regs;
	Int16 i;
	while (1) {
		for (i = 0; i < I2S_DMA_BUFFER_SIZE; i++) {
			mod = sin_gen(&ss_mod, 0);
			mod_scaled = (mod_depth * mod * SINTABLE_LENGTH * 4) / ( 205887 );


			output = sin_gen(&ss_carrier, 0) >> 6;
			dmaPingSrcBuf[i] = output;
			TSK_sleep(10);
		}

//		printf("%d\n", output);


//
//		EZDSP5535_I2S_writeLeft( output );
//		EZDSP5535_I2S_writeRight( output );
	}
}



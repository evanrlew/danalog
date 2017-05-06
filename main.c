/*
 *  Copyright 2010 by Texas Instruments Incorporated.
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */
/***************************************************************************/
/*                                                                         */
/*     H E L L O . C                                                       */
/*                                                                         */
/*     Basic LOG event operation from main.                                */
/*                                                                         */
/***************************************************************************/

#include <std.h>
#include "stdio.h"
#include <log.h>

#include "ezdsp5535.h"
#include "ezdsp5535_i2s.h"
#include "ezdsp5535_i2c.h"

#include "hellocfg.h"
#include "aic3204.h"
#include "singen.h"
#include "sintable.h"


/*
 *  ======== main ========
 */
Void main()
{
		printf("Initializing bsl\n");
		EZDSP5535_init( );

		printf("Init i2c\n");
		EZDSP5535_I2C_init( );

		printf("init i2s\n");
		EZDSP5535_I2S_init();

		printf("Initializing aic3204\n");
		aic3204_init();

		Int16 freq = 500;
		Int16 mod_ratio = 1;
		Int16 mod_depth = 5;

		SinState ss_carrier;
		sin_compute_params(&ss_carrier, freq);

		SinState ss_mod;
		sin_compute_params(&ss_mod, freq * mod_ratio);



		Int16 output, mod_scaled;
		Int32 mod;
		while (1) {
			mod = sin_gen(&ss_mod, 0);
			mod_scaled = (mod_depth * mod * SINTABLE_LENGTH * 4) / ( 205887 );


			output = sin_gen(&ss_carrier, mod_scaled) >> 8;
//			printf("%d\n", output);


			EZDSP5535_I2S_writeLeft( output );
			EZDSP5535_I2S_writeRight( output );
		}


    /* fall into DSP/BIOS idle loop */
}

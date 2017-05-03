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


		SinState ss;
		sin_compute_params(&ss, 1000);

		Int16 output;
		while (1) {
			output = sin_gen(&ss);
//			printf("%d\n", output);


			EZDSP5535_I2S_writeLeft( output );
			EZDSP5535_I2S_writeRight( output );
		}


    /* fall into DSP/BIOS idle loop */
    return;
}

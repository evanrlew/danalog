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

#include "gen_sound.h"
#include "i2s_dma.h"

#include "csl_intc.h"

extern void VECSTART(void); // defined in vector table
CSL_IRQ_Dispatch     dispatchTable;

/*
 *  ======== main ========
 */
Void main()
{
	printf("Initializing bsl\n");
	EZDSP5535_init( );

	printf("Init i2c\n");
	EZDSP5535_I2C_init( );

	//printf("init i2s\n");
	//EZDSP5535_I2S_init();

	printf("Initializing aic3204\n");
	aic3204_init();

	printf("Initializing dma with i2s");
	i2s_dma_init();



	//IRQ_globalEnable();



    /* fall into DSP/BIOS idle loop */
}

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
#include "i2s_dma.h"
#include "spi_config.h"

#include "csl_general.h"
#include "csl_intc.h"


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

	printf("Initializing spi");
	spi_init();

	Uint16 receive_arr[40];
	int i;
	for (i = 0; i<40; i++) {
		receive_arr[i] = 0;
	}
    Uint16 message = SPI_SWT_CMD;
	while(1) {
		spi_write(&message, 1);
		EZDSP5535_waitusec( 10 );
		spi_read(receive_arr, 1);
	}

    /* fall into DSP/BIOS idle loop */
}

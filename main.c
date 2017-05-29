/* Standard C includes */
#include <stdio.h>

/* DSP/BIOS headers */
#include <std.h>
#include "hellocfg.h"

/* ezDSP C5535 board specific headers */
#include "ezdsp5535.h"
#include "ezdsp5535_i2c.h"

/* C55xx chip support library headers */


/* Danalog headers */
#include "pconfig/aic3204.h"
#include "pconfig/i2s_dma.h"
#include "pconfig/spi_config.h"
#include "io/midi_queue.h"

Void main()
{
	printf("Initializing bsl\n");
	EZDSP5535_init( );

	printf("Init i2c\n");
	EZDSP5535_I2C_init( );

	printf("Initializing aic3204\n");
	aic3204_init();

	printf("Initializing dma with i2s");
	i2s_dma_init();

	printf("Initializing spi");
	midi_buffer_init();
	spi_init();

    /* fall into DSP/BIOS idle loop */
}


/* Standard C includes */
#include <stdio.h>

/* DSP/BIOS headers */
#include <log.h>
#include <tsk.h>
#include "hellocfg.h"

/* ezDSP C5535 board specific headers */
#include "ezdsp5535.h"
#include "ezdsp5535_i2c.h"

/* C55xx chip support library headers */


/* Danalog headers */
#include "drivers/aic3204.h"
#include "drivers/i2s_dma.h"
#include "drivers/spi_config.h"
#include "global_vars.h"



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
	spi_init();

    /* fall into DSP/BIOS idle loop */
}

Void spi_get_midi( void )
{
	while (1) {
		Uint16 message = SPI_MIDI_CMD;
		TSK_disable();
		spi_write(&message, 1);
		spi_read(midi, 3);
		TSK_enable();
		TSK_sleep(5);
	}
}

Void spi_get_interface_controls( void )
{
	Uint16 counter = 0;
	Uint16 message;
	while (1) {
		switch(counter) {
		case 0:
			message = SPI_SWT_CMD;
			TSK_disable();
			spi_write(&message, 1);
			spi_read(&switches, 1);
			TSK_enable();
			break;
		case 1:
			message = SPI_ENC_CMD;
			TSK_disable();
			spi_write(&message, 1);
			spi_read(encoders, 19);
			TSK_enable();
			break;
		case 2:
			message = SPI_POT_CMD;
			TSK_disable();
			spi_write(&message, 1);
			spi_read(pots, 8);
			TSK_enable();
			break;
		default:
			while (1); // error
		}

		counter = (counter + 1) % 3;
		TSK_sleep(25); // service every 5ms
	}
}

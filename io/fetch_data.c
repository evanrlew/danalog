/* Standard C includes */
#include <stdio.h>

/* DSP/BIOS headers */
#include <std.h>
#include <tsk.h>
#include "hellocfg.h"

/* ezDSP C5535 board specific headers */
#include "ezdsp5535.h"

/* C55xx chip support library headers */


/* Danalog headers */
#include "../pconfig/aic3204.h"
#include "../pconfig/i2s_dma.h"
#include "../pconfig/spi_config.h"
#include "../io/midi_queue.h"
#include "../global_vars.h"

Void spi_get_midi( void )
{
	while (1) {
		Uint16 message = SPI_MIDI_CMD;
		TSK_disable();
		while (1) {
			spi_write(&message, 1);
			spi_read(midi, 3);
			// if the fist byte is 0, no new midi information
			if ( (midi[0] & 0x80) == 0) { break; } // this is a hack for the slow avr isr

			MidiPacket p;
			p.midi_cmd = midi[0];
			p.note_id  = midi[1];
			p.velocity = midi[2];

			midi_buffer_write(p);

		}
		TSK_enable();
		TSK_sleep(10);
	}
}

Void spi_get_interface_controls( void )
{
//	Uint16 counter = 0;
//	Uint16 message;
//	while (1) {
//		switch(counter) {
//		case 0:
//			message = SPI_SWT_CMD;
//			TSK_disable();
//			spi_write(&message, 1);
//			spi_read(&switches, 1);
//			TSK_enable();
//			break;
//		case 1:
//			message = SPI_ENC_CMD;
//			TSK_disable();
//			spi_write(&message, 1);
//			spi_read(encoders, 19);
//			TSK_enable();
//			break;
//		case 2:
//			message = SPI_POT_CMD;
//			TSK_disable();
//			spi_write(&message, 1);
//			spi_read(pots, 8);
//			TSK_enable();
//			break;
//		default:
//			while (1); // error
//		}
//
//		counter = (counter + 1) % 3;
//		TSK_sleep(75); // service every 5ms
//	}
}

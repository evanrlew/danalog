/*
 * eq.c
 *
 *  Created on: Jun 1, 2017
 *      Author: evan
 */


/* Standard C includes */
#include <std.h>
#include <stdio.h>
#include <tsk.h>
#include "audio/singen.h"
#include "global_vars.h"

#pragma DATA_SECTION(Buffer, "Buffer");
Int16 Buffer[256];


Void eq_tsk( Void ) {
	volatile Int16 counter = 0;
	SinState EQSine;
	sin_compute_params(&EQSine, 6000);
	Int8 i;
	while(1) {
		// eq code
		for (i = 0; i < 256; ++i) {
			Buffer[i] = sin_gen(&EQSine, 0);
		}
		Uint8 Knob_Values[5] = {pots[0], pots[1], pots[2], pots[3], pots[4]};
		printf("%d %d %d %d %d\n", pots[0], pots[1], pots[2], pots[3], pots[4]);
		Uint8 EqKIndex[5] = {1, 3, 9, 27, 81};
		Uint8 Interval_Lengths[4] = {2, 6, 18, 54};
		Int8 EqualizerFD[256];
		EqualizerFD[0] = Knob_Values[0];
		//printf("Equalizer Values\n%d,",EqualizerFD[0]);
		EqualizerFD[1] = Knob_Values[0];
		//printf("%d,",EqualizerFD[1]);
		Uint8 l;
		Uint8 m;
		Uint8 n;
		Int8 Interp_M;
		for(l = 0; l < 4; l++) {
		//make array
		   	n = 1;
		   	Interp_M = (Knob_Values[l+1] - Knob_Values[l]) / Interval_Lengths[l];
		   	for(m = EqKIndex[l]+1; m < EqKIndex[l+1]; m++) {
		   		EqualizerFD[m] = Knob_Values[l] + Interp_M * n;
		   		n++;
//		   		printf("%d,",EqualizerFD[m]);
		   	}
		   	EqualizerFD[m] = Knob_Values[l+1];
//		   	printf("%d,",EqualizerFD[m]);
		}
		for(l = 82; l < 128; l++) {
		   	EqualizerFD[l] = Knob_Values[4];
//		    printf("%d,",EqualizerFD[l]);
		}
		for(i = 0;i < 128; i++) {
		   	EqualizerFD[255-i] = EqualizerFD[i];
//		   	printf("%d, ",EqualizerFD[128+i]);
		}

		//cfft_SCALE(complex_data, 256);
		//cbrev(complex_data, complex_data, 256);
		TSK_sleep(100);
	}
}


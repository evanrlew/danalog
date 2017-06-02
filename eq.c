/*
 * eq.c
 *
 *  Created on: Jun 1, 2017
 *      Author: evan
 */


/* Standard C includes */
#include <std.h>
#include <stdio.h>
#include <math.h>
#include <tsk.h>
#include "Dsplib.h"
#include "audio/singen.h"
#include "global_vars.h"
#include "TMS320.H"

#pragma DATA_SECTION(Buffer, "Buffer");
Int16 Buffer[256];
//#pragma DATA_SECTION(complex_data,"complex_data");
DATA complex_data[512];


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
//		Uint8 Knob_Values[5] = {pots[0], pots[1], pots[2], pots[3], pots[4]};
		Int16 Knob_Values[5] = {1, 10, 20, 40, 30};
		//printf("%d %d %d %d %d\n", Knob_Values[0], Knob_Values[1], Knob_Values[2], Knob_Values[3], Knob_Values[4]);
		Int16 EqKIndex[5] = {1, 3, 9, 27, 81};
		Int16 Interval_Lengths[4] = {2, 6, 18, 54};
		Int16 EqualizerFD[256];
		EqualizerFD[0] = Knob_Values[0];
		//printf("\n%i,",EqualizerFD[0]);
		EqualizerFD[1] = Knob_Values[0];
		//printf("%i,",EqualizerFD[1]);
		Int16 l;
		Int16 m;
		Int16 n;
		Int16 Interp_M;
		for(l = 0; l < 4; l++) {
		//make array
		   	n = 1;
		   	Interp_M = (Knob_Values[l+1] - Knob_Values[l]) / Interval_Lengths[l];
		   	for(m = EqKIndex[l]+1; m < EqKIndex[l+1]; m++) {
		   		EqualizerFD[m] = Knob_Values[l] + Interp_M * n;
		   		n++;
		   		//printf("%i,",EqualizerFD[m]);
		   	}
		   	EqualizerFD[m] = Knob_Values[l+1];
		   	//printf("%i,",EqualizerFD[m]);
		}
		for(l = 82; l < 128; l++) {
		   	EqualizerFD[l] = Knob_Values[4];
		    //printf("%i,",EqualizerFD[l]);
		}
		for(i = 0;i < 128; i++) {
		   	EqualizerFD[255-i] = EqualizerFD[i];
		   	//printf("%i,",EqualizerFD[128+i]);
		}
		printf("\n");
		for(i=0;i<256;i++) {
			complex_data[2*i] = EqualizerFD[i];
			complex_data[2*i+1] = 0;
			//printf("%d, ", complex_data[2*i]);
		}
		for(i=0;i<512;i++) {
			printf("%d, ", complex_data[i]);
		}
		cifft_SCALE(complex_data, 256)
		//cfft_SCALE(complex_data, 256);
		//cbrev(complex_data, complex_data, 256);
		TSK_sleep(100);
	}
}

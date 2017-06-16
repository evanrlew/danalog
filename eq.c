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
#include "Dsplib_c.h"
#include "MISC.H"
#include "audio/singen.h"
#include "global_vars.h"
#include "TMS320.H"

/* DSP/BIOS headers */
#include "hellocfg.h"


//#pragma DATA_SECTION(Buffer, "Buffer");
//Int16 Buffer[256];
//#pragma DATA_ALIGN (complex_data, 4)
#pragma DATA_ALIGN (output_left_ping, 4)
Int16 output_left_ping[I2S_DMA_BUFFER_SIZE];

#pragma DATA_ALIGN (output_left_pong, 4)
Int16 output_left_pong[I2S_DMA_BUFFER_SIZE];

#pragma DATA_ALIGN (output_right_ping, 4)
Int16 output_right_ping[I2S_DMA_BUFFER_SIZE];

#pragma DATA_ALIGN (output_right_pong, 4)
Int16 output_right_pong[I2S_DMA_BUFFER_SIZE];

Int16* x;
Int32 Ak1[3] = {10000, -15996, 6401};
Int32 Bk1[3] = {1799, 0, -1799};
Int32 Ak2[3] = {10000, -17752, 7921};
Int32 Bk2[3] = {1043, 0, -1043};
Int32 Ak3[3] = {10000, -15416, 6241};
Int32 Bk3[3] = {1880, 0, -1880};
Int32 Ak4[3] = {10000, -10880, 4761};
Int32 Bk4[3] = {2618, 0, -2618};
Int32 Ak5[3] = {10000, 4782, 3481};
Int32 Bk5[3] = {3257, 0, -3257};
Int32 y1[128] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
Int32 Next_y1[128];
Int32 y2[128];
Int32 Next_y2[128];
Int32 y3[128];
Int32 Next_y3[128];
Int32 y4[128];
Int32 Next_y4[128];
Int32 y5[128];
Int32 Next_y5[128];
Int32 y[128];
Int32 First_Term = 0;
Int32 Second_Term = 0;
Int32 Third_Term = 0;
//Int16 nx = 128;
//Int16 nh = 3;
//DATA x[128];
//DATA h[3] = {10,14,10};
//DATA r[128];
//DATA dbuffer[5] = {0,0,0,0};
//Int16 oflag;
Int16 var = 0;

//Int16 delay = 500;
//Int16 nx = 128;
//Int16 nh = 501;
//DATA x[128];
//DATA h[501];
//DATA r[128];
//DATA dbuffer[501];
//Int16 oflag;
//Int16 var = 0;

Void eq_tsk( Void ) {
	volatile Int16 counter = 0;
	SinState EQSine;
	sin_compute_params(&EQSine, 6000);
	Int16 i;
	// determine which buffer to fill

//	for (i = 0; i < 128; ++i) {
//		x[i] = sin_gen(&EQSine, 0);
//	}
	Next_y1[0] = Bk1[0]*x[0]/Ak1[0]/(pots[0]+1);
	Next_y1[1] = (Bk1[0]*x[1]+Bk1[1]*x[0]-Ak1[1]*y1[0])/Ak1[0]/(pots[0]+1);
	Next_y1[2] = (Bk1[0]*x[2]+Bk1[1]*x[1]+Bk1[2]*x[0]-Ak1[1]*y1[1]-Ak1[2]*y1[0])/Ak1[0]/(pots[0]+1);
	Next_y2[0] = Bk2[0]*x[0]/Ak2[0]/(pots[1]+1);
	Next_y2[1] = (Bk2[0]*x[1]+Bk2[1]*x[0]-Ak2[1]*y2[0])/Ak2[0]/(pots[1]+1);
	Next_y2[2] = (Bk2[0]*x[2]+Bk2[1]*x[1]+Bk2[2]*x[0]-Ak2[1]*y2[1]-Ak2[2]*y2[0])/Ak2[0]/(pots[1]+1);
	Next_y3[0] = Bk3[0]*x[0]/Ak3[0]/(pots[2]+1);
	Next_y3[1] = (Bk3[0]*x[1]+Bk3[1]*x[0]-Ak3[1]*y3[0])/Ak3[0]/(pots[2]+1);
	Next_y3[2] = (Bk3[0]*x[2]+Bk3[1]*x[1]+Bk3[2]*x[0]-Ak3[1]*y3[1]-Ak3[2]*y3[0])/Ak3[0]/(pots[2]+1);
	Next_y4[0] = Bk4[0]*x[0]/Ak4[0]/(pots[3]+1);
	Next_y4[1] = (Bk4[0]*x[1]+Bk4[1]*x[0]-Ak4[1]*y4[0])/Ak4[0]/(pots[3]+1);
	Next_y4[2] = (Bk4[0]*x[2]+Bk4[1]*x[1]+Bk4[2]*x[0]-Ak4[1]*y4[1]-Ak4[2]*y4[0])/Ak4[0]/(pots[3]+1);
	Next_y5[0] = Bk5[0]*x[0]/Ak5[0]/(pots[4]+1);
	Next_y5[1] = (Bk5[0]*x[1]+Bk5[1]*x[0]-Ak5[1]*y5[0])/Ak5[0]/(pots[4]+1);
	Next_y5[2] = (Bk5[0]*x[2]+Bk5[1]*x[1]+Bk5[2]*x[0]-Ak5[1]*y5[1]-Ak5[2]*y5[0])/Ak5[0]/(pots[4]+1);
	while(1) {
		SEM_pend(&output_sem, SYS_FOREVER);
		SEM_post(&ag_sem);
		if (CSL_DMA1_REGS->DMACH0TCR2 & 0x0002) { // last xfer: pong
			x = &ag_left_pong;
			x = &ag_right_pong;
		} else {
			x = &ag_left_ping;
			x = &ag_right_ping;
		}
//		Ak1[i]*y1[i]+Ak1[i-1]*y1[i-1]+Ak1[i-2]*y1[i-2] = Bk1[i]*x[i]+Bk1[i-1]*x[i-1]+Bk1[i-2]*x[i-2]
//		y1[i] = (Bk1[0]*x[i]+Bk1[1]*x[i-1]+Bk1[2]*x[i-2]-Ak1[1]*y1[i-1]-Ak1[2]*y1[i-2])/Ak1[0];
		y1[0] = Next_y1[0];
		y1[1] = Next_y1[1];
		y1[2] = Next_y1[2];
		for (i = 3; i < 128; i++) {
			y1[i] = (Bk1[0]*x[i]+Bk1[1]*x[i-1]+Bk1[2]*x[i-2]-Ak1[1]*y1[i-1]-Ak1[2]*y1[i-2])/Ak1[0]/(pots[0]+1);
		}
		Next_y1[0] = y1[125];
		Next_y1[1] = y1[126];
		Next_y1[2] = y1[127];
		//there is only one Bandpass done now
		y2[0] = Next_y2[0];
		y2[1] = Next_y2[1];
		y2[2] = Next_y2[2];
		for (i = 3; i < 128; i++) {
			y2[i] = (Bk2[0]*x[i]+Bk2[1]*x[i-1]+Bk2[2]*x[i-2]-Ak2[1]*y2[i-1]-Ak2[2]*y2[i-2])/Ak2[0]/(pots[1]+1);
		}
		Next_y2[0] = y2[125];
		Next_y2[1] = y2[126];
		Next_y2[2] = y2[127];
		// there is now two bandpasses done
		y3[0] = Next_y3[0];
		y3[1] = Next_y3[1];
		y3[2] = Next_y3[2];
		for (i = 3; i < 128; i++) {
			y3[i] = (Bk3[0]*x[i]+Bk3[1]*x[i-1]+Bk3[2]*x[i-2]-Ak3[1]*y3[i-1]-Ak3[2]*y3[i-2])/Ak3[0]/(pots[2]+1);
		}
		Next_y3[0] = y3[125];
		Next_y3[1] = y3[126];
		Next_y3[2] = y3[127];
		// there is now three bandpasses done
		y4[0] = Next_y4[0];
		y4[1] = Next_y4[1];
		y4[2] = Next_y4[2];
		for (i = 3; i < 128; i++) {
			y4[i] = (Bk4[0]*x[i]+Bk4[1]*x[i-1]+Bk4[2]*x[i-2]-Ak4[1]*y4[i-1]-Ak4[2]*y4[i-2])/Ak4[0]/(pots[3]+1);
		}
		Next_y4[0] = y4[125];
		Next_y4[1] = y4[126];
		Next_y4[2] = y4[127];
		// fourth bandpass complete
		y5[0] = Next_y5[0];
		y5[1] = Next_y5[1];
		y5[2] = Next_y5[2];
		for (i = 3; i < 128; i++) {
			y5[i] = (Bk5[0]*x[i]+Bk5[1]*x[i-1]+Bk5[2]*x[i-2]-Ak5[1]*y5[i-1]-Ak5[2]*y5[i-2])/Ak5[0]/(pots[4]+1);
		}
		Next_y5[0] = y5[125];
		Next_y5[1] = y5[126];
		Next_y5[2] = y5[127];
		// fifth bandpass complete
		//combine into y[]
		for (i = 0; i < 128; i++) {
			y[i] = y1[i]/5 + y2[i]/5 + y3[i]/5 + y4[i]/5 + y5[i]/5;
		}
		// determine which buffer to fill
		Int16 *left_output, *right_output;
		if (CSL_DMA1_REGS->DMACH0TCR2 & 0x0002) { // last xfer: pong
			left_output = output_left_pong;
			right_output = output_right_pong;
		} else {
			left_output = output_left_ping;
			right_output = output_right_ping;
		}
		for (i = 0; i < I2S_DMA_BUFFER_SIZE; i++) {
			left_output[i] = y1[i];
			right_output[i] = y1[i];
		}
//		First_Term = Bk[0]*x[0];
//		y[0] = First_Term/Ak;
//		First_Term = Bk[0]*x[1];
//		Second_Term = Bk[1]*x[0];
//		Third_Term = 0;
//		y[1] = First_Term + Second_Term;
//		y[1] = y[1]/Ak;
//		First_Term = Bk[0]*x[2];
//		Second_Term = Bk[1]*x[1];
//		Third_Term = Bk[2]*x[0];
//		y[2] = First_Term + Second_Term + Third_Term;
//		y[2] = y[2]/Ak;
//
//		for (var = 3; var < 128; ++var) {
//			First_Term = Bk[0]*x[var];
//			Second_Term = Bk[1]*x[var-1];
//			Third_Term = Bk[2]*x[var-2];
//			y[var] = First_Term + Second_Term + Third_Term;
//			y[var] = y[var]/Ak;
////			y[i] = (Bk[0]*x[i] + Bk[1]*x[i-1] + Bk[2]*x[i-2])/Ak;
//			//printf("%d,", y[i]);
//		}

////		Uint8 Knob_Values[5] = {pots[0], pots[1], pots[2], pots[3], pots[4]};
//		Int16 Knob_Values[5] = {1, 10, 20, 40, 30};
//		//printf("%d %d %d %d %d\n", Knob_Values[0], Knob_Values[1], Knob_Values[2], Knob_Values[3], Knob_Values[4]);
//		Int16 EqKIndex[5] = {1, 3, 9, 27, 81};
//		Int16 Interval_Lengths[4] = {2, 6, 18, 54};
//		Int16 EqualizerFD[256];
//		EqualizerFD[0] = Knob_Values[0];
//		//printf("\n%i,",EqualizerFD[0]);
//		EqualizerFD[1] = Knob_Values[0];
//		//printf("%i,",EqualizerFD[1]);
//		Int16 l;
//		Int16 m;
//		Int16 n;
//		Int16 Interp_M;
//		for(l = 0; l < 4; l++) {
//		//make array
//		   	n = 1;
//		   	Interp_M = (Knob_Values[l+1] - Knob_Values[l]) / Interval_Lengths[l];
//		   	for(m = EqKIndex[l]+1; m < EqKIndex[l+1]; m++) {
//		   		EqualizerFD[m] = Knob_Values[l] + Interp_M * n;
//		   		n++;
//		   		//printf("%i,",EqualizerFD[m]);
//		   	}
//		   	EqualizerFD[m] = Knob_Values[l+1];
//		   	//printf("%i,",EqualizerFD[m]);
//		}
//		for(l = 82; l < 128; l++) {
//		   	EqualizerFD[l] = Knob_Values[4];
//		    //printf("%i,",EqualizerFD[l]);
//		}
//		for(i = 0;i < 128; i++) {
//		   	EqualizerFD[255-i] = EqualizerFD[i];
//		   	//printf("%i,",EqualizerFD[128+i]);
//		}
//		printf("\n");
//		for(i=0;i<256;i++) {
//			complex_data[2*i] = EqualizerFD[i];
//			complex_data[2*i+1] = 0;
//			//printf("%d, ", complex_data[2*i]);
//		}
//		for(i=0;i<512;i++) {
//			printf("%d, ", complex_data[i]);
//		}
//		cifft_SCALE(complex_data, 256);
		//cfft_SCALE(complex_data, 256);
		//cbrev(complex_data, complex_data, 256);
		TSK_sleep(100);
	}
}

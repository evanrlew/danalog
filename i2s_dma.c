/*
 * i2s_dma.c
 *
 *  Created on: May 8, 2017
 *      Author: evan
 */


#include <stdio.h>
#include "ezdsp5535_i2s.h"
#include "i2s_dma.h"

#include "soc.h"
#include "cslr.h"
#include "cslr_sysctrl.h"

#include "csl_gpio.h"
#include "csl_i2s.h"
#include "csl_intc.h"

#include "singen.h"
#include "sintable.h"


#pragma DATA_ALIGN (dmaPingSrcBuf, 4)
Int16 dmaPingSrcBuf[I2S_DMA_BUFFER_SIZE];

#pragma DATA_ALIGN (dmaPongSrcBuf, 4)
Int16 dmaPongSrcBuf[I2S_DMA_BUFFER_SIZE];

Int32 isrCounterPing = 0;
Int32 isrCounterPong = 0;

Int16 freq = 500;
Int16 mod_ratio = 1;
Int16 mod_depth = 5;

SinState ss_carrier;
SinState ss_mod;

Int16 i;


Int16 output, mod_scaled;
Int16 mod;


CSL_DmaRegsOvly dma_reg;

void i2s_dma_init( void )
{


	sin_compute_params(&ss_carrier, freq);
	sin_compute_params(&ss_mod, freq * mod_ratio);

	CSL_Status 			status;

	// Configure I2S
	CSL_I2sHandle i2sHandle;
	I2S_Config i2sConfig;

	i2sHandle = I2S_open(I2S_INSTANCE2, DMA_INTERRUPT, I2S_CHAN_STEREO);

    /* Set the value for the configure structure */
	i2sConfig.dataFormat     = I2S_DATAFORMAT_LJUST;
	i2sConfig.dataType       = I2S_STEREO_ENABLE;
	i2sConfig.loopBackMode   = I2S_LOOPBACK_DISABLE;
	i2sConfig.fsPol          = I2S_FSPOL_LOW;
	i2sConfig.clkPol         = I2S_RISING_EDGE; //I2S_FALLING_EDGE;
	i2sConfig.datadelay      = I2S_DATADELAY_ONEBIT;
	i2sConfig.datapack       = I2S_DATAPACK_DISABLE;
	i2sConfig.signext        = I2S_SIGNEXT_DISABLE;
	i2sConfig.wordLen        = I2S_WORDLEN_16;
	i2sConfig.i2sMode        = I2S_SLAVE;
	i2sConfig.clkDiv         = I2S_CLKDIV2; // don't care for slave mode
	i2sConfig.fsDiv          = I2S_FSDIV32; // don't care for slave mode
	i2sConfig.FError         = I2S_FSERROR_DISABLE;
	i2sConfig.OuError        = I2S_OUERROR_DISABLE;

	status = I2S_setup(i2sHandle, &i2sConfig);
	CSL_I2S2_REGS->I2SINTMASK &= 0xFF80;
	I2S_transEnable(i2sHandle, TRUE);

	// Init DMA
	status = DMA_init();


	/* Set the reset clock cycle */
	CSL_FINS(CSL_SYSCTRL_REGS->PSRCR, SYS_PSRCR_COUNT,
	CSL_DMA_RESET_CLOCK_CYCLE);
	CSL_FINST(CSL_SYSCTRL_REGS->PRCR, SYS_PRCR_DMA_RST, RST);

	/* Enable the corresponding DMA clock from PCGCR Registers */
	CSL_FINST(CSL_SYSCTRL_REGS->PCGCR1, SYS_PCGCR1_DMA0CG, ACTIVE);
	CSL_FINST(CSL_SYSCTRL_REGS->PCGCR2, SYS_PCGCR2_DMA1CG, ACTIVE);
	CSL_FINST(CSL_SYSCTRL_REGS->PCGCR2, SYS_PCGCR2_DMA2CG, ACTIVE);
	CSL_FINST(CSL_SYSCTRL_REGS->PCGCR2, SYS_PCGCR2_DMA3CG, ACTIVE);



	/* enable ch4 DMA interrupts */
	CSL_SYSCTRL_REGS->DMAIER = 0x0010;

	/* Clear all DMA interrupt flags */
	CSL_SYSCTRL_REGS->DMAIFR = 0xFFFF;
	//IRQ_clear(DMA_EVENT);.


	// Configure DMA
	CSL_DMA_Handle 		dmaHandle;
	CSL_DMA_Config 		dmaConfig;
	CSL_DMA_ChannelObj  dmaChannelObj;

	dmaConfig.pingPongMode = CSL_DMA_PING_PONG_ENABLE;
	dmaConfig.autoMode     = CSL_DMA_AUTORELOAD_ENABLE;
	dmaConfig.burstLen     = CSL_DMA_TXBURST_1WORD;
	dmaConfig.trigger      = CSL_DMA_EVENT_TRIGGER;
	dmaConfig.dmaEvt       = CSL_DMA_EVT_I2S2_TX;
	dmaConfig.dmaInt       = CSL_DMA_INTERRUPT_ENABLE;
	dmaConfig.chanDir      = CSL_DMA_WRITE;
	dmaConfig.trfType      = CSL_DMA_TRANSFER_IO_MEMORY;
	dmaConfig.dataLen      = I2S_DMA_BUFFER_SIZE * 4;
	dmaConfig.srcAddr      = (Uint32)dmaPingSrcBuf;
	dmaConfig.destAddr     = (Uint32)0x2A08;





	dmaHandle = DMA_open(CSL_DMA_CHAN4, &dmaChannelObj, &status);
	DMA_config(dmaHandle, &dmaConfig);
	dma_reg = dmaHandle->dmaRegs;


	/* Clear DMA Interrupt Flags */
	IRQ_clear(DMA_EVENT);

	/* Enable DMA Interrupt */
	IRQ_enable(DMA_EVENT);

	DMA_start(dmaHandle);

}

void dma_isr(void) {
	if (CSL_SYSCTRL_REGS->DMAIFR & 0x0010) { // ch4 interrupt
		Int16 i;
		Int16 output, mod_scaled;
		Int32 mod;

		if (dma_reg->DMACH0TCR2 & 0x0002) { // last xfer: pong
			isrCounterPing++;

#pragma MUST_ITERATE(I2S_DMA_BUFFER_SIZE,I2S_DMA_BUFFER_SIZE)
			for (i = 0; i < I2S_DMA_BUFFER_SIZE; i++) {
				mod = sin_gen(&ss_mod, 0);
				mod_scaled = (mod_depth * mod * SINTABLE_LENGTH * 4) / ( 205887 );


				output = sin_gen(&ss_carrier, mod_scaled) >> 6;
				dmaPongSrcBuf[i] = output;
			}
		} else { // last xfer: ping
			isrCounterPong++;

#pragma MUST_ITERATE(I2S_DMA_BUFFER_SIZE,I2S_DMA_BUFFER_SIZE)
			for (i = 0; i < I2S_DMA_BUFFER_SIZE; i++) {
				mod = sin_gen(&ss_mod, 0);
				mod_scaled = (mod_depth * mod * SINTABLE_LENGTH * 4) / ( 205887 );


				output = sin_gen(&ss_carrier, mod_scaled) >> 6;
				dmaPingSrcBuf[i] = output;
			}
		}
		CSL_SYSCTRL_REGS->DMAIFR |= 0x0010; // clear interrupt
	} else {
		while(1);
	}

}

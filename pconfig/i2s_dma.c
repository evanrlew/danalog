/*
 * i2s_dma.c
 *
 *  Created on: May 8, 2017
 *      Author: evan
 */


#include <stdio.h>
#include "ezdsp5535_i2s.h"
#include "i2s_dma.h"

#include "hellocfg.h"

#include "soc.h"
#include "cslr.h"
#include "cslr_sysctrl.h"

#include "csl_gpio.h"
#include "csl_i2s.h"
#include "csl_intc.h"

#include "../global_vars.h"



#pragma DATA_ALIGN (ag_left_ping, 4)
Int16 ag_left_ping[I2S_DMA_BUFFER_SIZE];

#pragma DATA_ALIGN (ag_left_pong, 4)
Int16 ag_left_pong[I2S_DMA_BUFFER_SIZE];

#pragma DATA_ALIGN (ag_right_ping, 4)
Int16 ag_right_ping[I2S_DMA_BUFFER_SIZE];

#pragma DATA_ALIGN (ag_right_pong, 4)
Int16 ag_right_pong[I2S_DMA_BUFFER_SIZE];





CSL_DmaRegsOvly dma_reg;

void i2s_dma_init( void )
{

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

	// Left DMA config
	CSL_DMA_Handle 		left_dmaHandle;
	CSL_DMA_Config 		left_dmaConfig;
	CSL_DMA_ChannelObj  left_dmaChannelObj;

	left_dmaConfig.pingPongMode = CSL_DMA_PING_PONG_ENABLE;
	left_dmaConfig.autoMode     = CSL_DMA_AUTORELOAD_ENABLE;
	left_dmaConfig.burstLen     = CSL_DMA_TXBURST_1WORD;
	left_dmaConfig.trigger      = CSL_DMA_EVENT_TRIGGER;
	left_dmaConfig.dmaEvt       = CSL_DMA_EVT_I2S2_TX;
	left_dmaConfig.dmaInt       = CSL_DMA_INTERRUPT_ENABLE;
	left_dmaConfig.chanDir      = CSL_DMA_WRITE;
	left_dmaConfig.trfType      = CSL_DMA_TRANSFER_IO_MEMORY;
	left_dmaConfig.dataLen      = I2S_DMA_BUFFER_SIZE * 4;
	left_dmaConfig.srcAddr      = (Uint32)output_left_ping;
	left_dmaConfig.destAddr     = (Uint32)0x2A08;

	left_dmaHandle = DMA_open(CSL_DMA_CHAN4, &left_dmaChannelObj, &status);
	DMA_config(left_dmaHandle, &left_dmaConfig);
	dma_reg = left_dmaHandle->dmaRegs;
	DMA_start(left_dmaHandle);

	// Left DMA config
	CSL_DMA_Handle 		right_dmaHandle;
	CSL_DMA_Config 		right_dmaConfig;
	CSL_DMA_ChannelObj  right_dmaChannelObj;

	right_dmaConfig.pingPongMode = CSL_DMA_PING_PONG_ENABLE;
	right_dmaConfig.autoMode     = CSL_DMA_AUTORELOAD_ENABLE;
	right_dmaConfig.burstLen     = CSL_DMA_TXBURST_1WORD;
	right_dmaConfig.trigger      = CSL_DMA_EVENT_TRIGGER;
	right_dmaConfig.dmaEvt       = CSL_DMA_EVT_I2S2_TX;
	right_dmaConfig.dmaInt       = CSL_DMA_INTERRUPT_DISABLE; // rely on iterrupt from left
	right_dmaConfig.chanDir      = CSL_DMA_WRITE;
	right_dmaConfig.trfType      = CSL_DMA_TRANSFER_IO_MEMORY;
	right_dmaConfig.dataLen      = I2S_DMA_BUFFER_SIZE * 4;
	right_dmaConfig.srcAddr      = (Uint32)output_right_ping;
	right_dmaConfig.destAddr     = (Uint32)0x2A0C;

	right_dmaHandle = DMA_open(CSL_DMA_CHAN5, &right_dmaChannelObj, &status);
	DMA_config(right_dmaHandle, &right_dmaConfig);
	dma_reg = right_dmaHandle->dmaRegs;
	DMA_start(right_dmaHandle);



	/* Clear DMA Interrupt Flags */
	IRQ_clear(DMA_EVENT);

	/* Enable DMA Interrupt */
	IRQ_enable(DMA_EVENT);





}

void dma_isr(void) {
	if (CSL_SYSCTRL_REGS->DMAIFR & 0x0010) { // ch4 interrupt, left channel
		SEM_post(&ag_sem);
		CSL_SYSCTRL_REGS->DMAIFR |= 0x0010; // clear interrupt
	} else {
		while(1);
	}

}

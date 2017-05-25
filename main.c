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

#include "csl_general.h"
#include "csl_intc.h"
#include "csl_spi.h"
#include "csl_gpio.h"

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



	// SPI!!!
	CSL_SpiHandle	hSpi;
	SPI_Config		hwConfig;

	// init spi
	volatile Uint16 delay;
	ioport volatile CSL_SysRegs	*sysRegs;

	sysRegs = (CSL_SysRegs *)CSL_SYSCTRL_REGS;
	CSL_FINS(sysRegs->PCGCR1, SYS_PCGCR1_SPICG, CSL_SYS_PCGCR1_SPICG_ACTIVE);

	/* Value of 'Reset Counter' */
	CSL_FINS(sysRegs->PSRCR, SYS_PSRCR_COUNT, 0x20);

	CSL_FINS(sysRegs->PRCR, SYS_PRCR_PG4_RST, CSL_SYS_PRCR_PG4_RST_RST);

	for(delay = 0; delay < 100; delay++);


	CSL_FINS(sysRegs->EBSR, SYS_EBSR_PPMODE, CSL_SYS_EBSR_PPMODE_MODE6);
	// done initing

	hSpi = SPI_open(SPI_CS_NUM_1, SPI_POLLING_MODE);

	hwConfig.spiClkDiv	= 100;
	hwConfig.wLen		= SPI_WORD_LENGTH_8;
	hwConfig.frLen		= 4;
	hwConfig.wcEnable	= SPI_WORD_IRQ_ENABLE;
	hwConfig.fcEnable	= SPI_FRAME_IRQ_DISABLE;
	hwConfig.csNum		= SPI_CS_NUM_1;
	hwConfig.dataDelay	= SPI_DATA_DLY_0;
	hwConfig.csPol		= SPI_CSP_ACTIVE_LOW;
	hwConfig.clkPol		= SPI_CLKP_LOW_AT_IDLE;
	hwConfig.clkPh		= SPI_CLK_PH_RISE_EDGE;

	SPI_config(hSpi, &hwConfig);

	// enable level shifter
	CSL_GpioObj    gpioObj;
	CSL_GpioObj    *hGpio;
	CSL_Status     status;

    hGpio = GPIO_open(&gpioObj, &status);

	/* Configure GPIO pin 0 as output pin */
	CSL_GpioPinConfig    config;
	config.pinNum    = CSL_GPIO_PIN13;
	config.direction = CSL_GPIO_DIR_OUTPUT;
	config.trigger   = CSL_GPIO_TRIG_CLEAR_EDGE;

	GPIO_configBit(hGpio, &config);
	GPIO_write(hGpio, CSL_GPIO_PIN13, 1);


	Uint16 test_array[4] = {1,2,3,4};
	while(1){
		SPI_dataTransaction(hSpi, test_array, 4, SPI_WRITE);
	}




    /* fall into DSP/BIOS idle loop */
}

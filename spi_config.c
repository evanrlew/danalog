/*
 * spi_config.c
 *
 *  Created on: May 25, 2017
 *      Author: evan
 */

#include "spi_config.h"
#include "csl_gpio.h"

#define SPI_RW_WAIT 25

SPI_Config		spi_hwConfig;

void spi_init( void ) {
	/*********************************
	 *    Configure SPI peripheral   *
	 *********************************/

	// Copy and paste from CSL, but changed
	// pin multiplexing mode to PPMODE_MODE6
	volatile Uint16 delay;
	ioport volatile CSL_SysRegs	*sysRegs;

//	sysRegs = (CSL_SysRegs *)CSL_SYSCTRL_REGS;
//	CSL_FINS(sysRegs->PCGCR1, SYS_PCGCR1_SPICG, CSL_SYS_PCGCR1_SPICG_ACTIVE);
//
//	/* Value of 'Reset Counter' */
//	CSL_FINS(sysRegs->PSRCR, SYS_PSRCR_COUNT, 0x20);
//
//	CSL_FINS(sysRegs->PRCR, SYS_PRCR_PG4_RST, CSL_SYS_PRCR_PG4_RST_RST);

	for(delay = 0; delay < 100; delay++);


	CSL_FINS(sysRegs->EBSR, SYS_EBSR_PPMODE, CSL_SYS_EBSR_PPMODE_MODE1);
	// End of CSL copy paste

	hSpi = SPI_open(SPI_CS_NUM_1, SPI_POLLING_MODE);

	spi_hwConfig.spiClkDiv	= 25;
	spi_hwConfig.wLen		= SPI_WORD_LENGTH_8;
	spi_hwConfig.frLen		= 1;
	spi_hwConfig.wcEnable	= SPI_WORD_IRQ_DISABLE;
	spi_hwConfig.fcEnable	= SPI_FRAME_IRQ_DISABLE;
	spi_hwConfig.csNum		= SPI_CS_NUM_1;
	spi_hwConfig.dataDelay	= SPI_DATA_DLY_0;
	spi_hwConfig.csPol		= SPI_CSP_ACTIVE_LOW;
	spi_hwConfig.clkPol		= SPI_CLKP_LOW_AT_IDLE;
	spi_hwConfig.clkPh		= SPI_CLK_PH_RISE_EDGE;

	SPI_config(hSpi, &spi_hwConfig);

	/*********************************************
	*      Enable level shifter (set OE high)    *
	*      GPIO pin 13                           *
	**********************************************/
	CSL_GpioObj    gpioObj;
	CSL_GpioObj    *hGpio;
	CSL_Status     status;

    hGpio = GPIO_open(&gpioObj, &status);

	CSL_GpioPinConfig    config;
	config.pinNum    = CSL_GPIO_PIN13;
	config.direction = CSL_GPIO_DIR_OUTPUT;
	config.trigger   = CSL_GPIO_TRIG_CLEAR_EDGE;

	GPIO_configBit(hGpio, &config);
	GPIO_write(hGpio, CSL_GPIO_PIN13, 1);
}

void spi_write( Uint16 *write_buf, Uint16 buf_len ) {
	// set frame length
	CSL_FINS(CSL_SPI_REGS->SPICMD1, SPI_SPICMD1_FLEN, buf_len-1);
	//SPI_write(hSpi, write_buf, buf_len);

	// swipped from cls_spi.c SPI_read
	volatile Uint16 	bufIndex;
	Uint16 	spiStatusReg;
	volatile Uint16 	spiBusyStatus;
	volatile Uint16 	spiWcStaus;
	volatile Uint16     delay;

	/* Write Word length set by the user */
	bufIndex = 0;
	while(bufIndex < buf_len)
	{
		CSL_SPI_REGS->SPIDR2 = (Uint16)(write_buf[bufIndex] << 0x08);
		CSL_SPI_REGS->SPIDR1 = 0x0000;
		bufIndex++;

		/* Set command for Writting to registers */
		CSL_FINS(CSL_SPI_REGS->SPICMD2, SPI_SPICMD2_CMD, SPI_WRITE_CMD);

		for(delay = 0; delay < SPI_RW_WAIT; delay++);

		do
		{
			spiStatusReg = CSL_SPI_REGS->SPISTAT1;
			spiBusyStatus = (spiStatusReg & CSL_SPI_SPISTAT1_BSY_MASK);
			spiWcStaus = (spiStatusReg & CSL_SPI_SPISTAT1_CC_MASK);
		}while((spiBusyStatus == CSL_SPI_SPISTAT1_BSY_BUSY) &&
				(spiWcStaus != CSL_SPI_SPISTAT1_CC_MASK));
	}
}

void spi_read( Uint16 *read_buf, Uint16 buf_len ) {
	// set frame length
	CSL_FINS(CSL_SPI_REGS->SPICMD1, SPI_SPICMD1_FLEN, buf_len-1);

	// swipped from cls_spi.c SPI_read
	volatile Uint16 	bufIndex;
	Int16 	spiStatusReg;
	volatile Int16 	spiBusyStatus;
	volatile Int16 	spiWcStaus;
	volatile Uint16 delay;

	bufIndex = 0;

	/* Read Word length set by the user */
	while(bufIndex < buf_len)
	{
		// Clear spi data regs
		CSL_SPI_REGS->SPIDR1 = 0;
		CSL_SPI_REGS->SPIDR2 = 0;

		/* Set command for reading buffer */
		CSL_FINS(CSL_SPI_REGS->SPICMD2, SPI_SPICMD2_CMD,
										CSL_SPI_SPICMD2_CMD_READ);

		for(delay = 0; delay < SPI_RW_WAIT; delay++);

		do
		{
			spiStatusReg = CSL_SPI_REGS->SPISTAT1;
			spiBusyStatus = (spiStatusReg & CSL_SPI_SPISTAT1_BSY_MASK);
			spiWcStaus = (spiStatusReg & CSL_SPI_SPISTAT1_CC_MASK);
		} while ((spiBusyStatus == CSL_SPI_SPISTAT1_BSY_BUSY) &&
				(spiWcStaus != CSL_SPI_SPISTAT1_CC_MASK));

		// read data
		read_buf[bufIndex] = (CSL_SPI_REGS->SPIDR1 & 0xFF);
		bufIndex++;
	}
}



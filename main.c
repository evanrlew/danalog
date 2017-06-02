/* Standard C includes */
#include <stdio.h>

/* DSP/BIOS headers */
#include <std.h>
#include "hellocfg.h"

/* ezDSP C5535 board specific headers */
#include "ezdsp5535.h"
#include "ezdsp5535_i2c.h"

/* C55xx chip support library headers */
#include "csl_pll.h"
#include "csl_general.h"
#include "csl_pllAux.h"


/* Danalog headers */
#include "pconfig/aic3204.h"
#include "pconfig/i2s_dma.h"
#include "pconfig/spi_config.h"
#include "io/midi_queue.h"

PLL_Obj pllObj;
PLL_Config pllCfg1;

PLL_Handle hPll;


PLL_Config pllCfg_12p288MHz = {0x8173, 0x8000, 0x0806, 0x0000};
PLL_Config pllCfg_40MHz     = {0x8988, 0x8000, 0x0806, 0x0201};
PLL_Config pllCfg_60MHz     = {0x8724, 0x8000, 0x0806, 0x0000};
PLL_Config pllCfg_75MHz     = {0x88ED, 0x8000, 0x0806, 0x0000};
PLL_Config pllCfg_100MHz    = {0x8BE8, 0x8000, 0x0806, 0x0000};
PLL_Config pllCfg_120MHz    = {0x8E4A, 0x8000, 0x0806, 0x0000};


//PLL_Config pllCfg_12p288MHz = {0x82ED, 0x8000, 0x0806, 0x0200};
//PLL_Config pllCfg_40MHz     = {0x8262, 0x8000, 0x0806, 0x0300};
//PLL_Config pllCfg_60MHz     = {0x81C8, 0xB000, 0x0806, 0x0000};
//PLL_Config pllCfg_75MHz     = {0x823B, 0x9000, 0x0806, 0x0000};
//PLL_Config pllCfg_100MHz    = {0x82FA, 0x8000, 0x0806, 0x0000};
//PLL_Config pllCfg_120MHz    = {0x8392, 0xA000, 0x0806, 0x0000};


PLL_Config *pConfigInfo;

#define CSL_TEST_FAILED         (1)
#define CSL_TEST_PASSED         (0)



Void main()
{

	printf("Initializing bsl\n");
	EZDSP5535_init( );

	/**** PLL init *****/
	CSL_Status status;

	status = PLL_init(&pllObj, CSL_PLL_INST_0);
	if(CSL_SOK != status)
	{
	   printf("PLL init failed \n");
	   return (status);
	}

	hPll = (PLL_Handle)(&pllObj);

	PLL_reset(hPll);

	status = PLL_bypass(hPll);
	if(CSL_SOK != status)
	{
	   printf("PLL bypass failed:%d\n",CSL_ESYS_BADHANDLE);
	   return(status);
	}

	/* Configure the PLL for 60MHz */
	pConfigInfo = &pllCfg_120MHz;

	status = PLL_config (hPll, pConfigInfo);
	if(CSL_SOK != status)
	{
	   printf("PLL config failed\n");
	   return(status);
	}

	status = PLL_getConfig(hPll, &pllCfg1);
	if(status != CSL_SOK)
	{
		printf("TEST FAILED: PLL get config... Failed.\n");
		printf ("Reason: PLL_getConfig failed. [status = 0x%x].\n", status);
		return(status);
	}

	printf("REGISTER --- CONFIG VALUES\n");

	printf("%04x --- %04x\n",pllCfg1.PLLCNTL1,hPll->pllConfig->PLLCNTL1);
	printf("%04x --- %04x Test Lock Mon will get set after PLL is up\n",
		   pllCfg1.PLLCNTL2,hPll->pllConfig->PLLCNTL2);
	printf("%04x --- %04x\n",pllCfg1.PLLINCNTL,hPll->pllConfig->PLLINCNTL);
	printf("%04x --- %04x\n",pllCfg1.PLLOUTCNTL,hPll->pllConfig->PLLOUTCNTL);

	EZDSP5535_waitusec(4000);

	status = PLL_enable(hPll);
	if(CSL_SOK != status)
	{
	   printf("PLL enable failed:%d\n",CSL_ESYS_BADHANDLE);
	   return(status);
	}

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


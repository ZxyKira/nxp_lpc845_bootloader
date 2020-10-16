/*-----------------------------------------------------------------------------------------
 *    File Name   :periph_io.c
 *    Version     :V1.0.0
 *    Create Date :2020-10-13
 *    Modufy Date :2020-10-13
 *    Information :
 */
#include <stdint.h>
#include <string.h>


#include "fw_chip.h"

#include "fsl_iocon.h"
#include "LPC845.h"
/*-----------------------------------------------------------------------------------------
 *    Parameter
 */
#define IOCON_PIO_CLKDIV0 0x00u      /*!<@brief IOCONCLKDIV0 */
#define IOCON_PIO_HYS_EN 0x20u       /*!<@brief Enable hysteresis */
#define IOCON_PIO_INV_DI 0x00u       /*!<@brief Input not invert */
#define IOCON_PIO_MODE_PULLUP 0x10u  /*!<@brief Selects pull-up function */
#define IOCON_PIO_OD_DI 0x00u        /*!<@brief Disables Open-drain function */
#define IOCON_PIO_SMODE_BYPASS 0x00u /*!<@brief Bypass input filter */
/*-----------------------------------------------------------------------------------------
 *    Extern Function/Variable
 */

/*-----------------------------------------------------------------------------------------
 *    Local Type/Structure
 */

/*-----------------------------------------------------------------------------------------
 *    Local Variable
 */
 
/*-----------------------------------------------------------------------------------------
 *    Variable
 */
fw_io_entity_t LED[8];
fw_io_entity_t BTN;

/*-----------------------------------------------------------------------------------------
 *    Inline Function
 */

/*-----------------------------------------------------------------------------------------
 *    Local Function
 */
static void periph_io_init(void){
	int i;
	
	for(i=0; i<8; i++){
		
		/* Get io PIO1_i profile to LED[i] */
		LED[i] = fw_io_api.getEntity(0, 1, i);
		fw_io_entity_api.setOutput(LED[i]);

		fw_io_entity_api.setLow(LED[i]);
		/* Set io to low */
	}
	BTN = fw_io_api.getEntity(0, 0, 12);
	fw_io_entity_api.setInput(BTN);
	CLOCK_EnableClock(kCLOCK_Iocon);
	
  const uint32_t IOCON_INDEX_BTN_config = (/* Selects pull-up function */
                                                 IOCON_PIO_MODE_PULLUP |
                                                 /* Enable hysteresis */
                                                 IOCON_PIO_HYS_EN |
                                                 /* Input not invert */
                                                 IOCON_PIO_INV_DI |
                                                 /* Disables Open-drain function */
                                                 IOCON_PIO_OD_DI |
                                                 /* Bypass input filter */
                                                 IOCON_PIO_SMODE_BYPASS |
                                                 /* IOCONCLKDIV0 */
                                                 IOCON_PIO_CLKDIV0);
	
	IOCON_PinMuxSet(IOCON, 0, IOCON_INDEX_BTN_config);
}
 
/*-----------------------------------------------------------------------------------------
 *    Public Function
 */
void periph_io_startup(){
	periph_io_init();
}

/*-----------------------------------------------------------------------------------------
 *    End of file
 */

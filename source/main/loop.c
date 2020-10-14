/*-----------------------------------------------------------------------------------------
 *    File Name   :loop.c
 *    Version     :V1.0.0
 *    Create Date :2020-10-12
 *    Modufy Date :2020-10-13
 *    Information :
 */
#include "fsl_power.h"
#include "fsl_clock.h"
#include "fsl_syscon.h"
#include "LPC845.h"
#include "stdio.h"

#include "fw_chip.h"

#include "TestingModule.h"
#include "TestingModuleGroup.h"
#include "net_scanner.h"

/*-----------------------------------------------------------------------------------------
 *    Parameter
 */
#define LOGOUT(fmt, ...) terminal_write(&terminal_cache[0], sprintf(&terminal_cache[0],fmt, ##__VA_ARGS__))

/*-----------------------------------------------------------------------------------------
 *    Extern Function/Variable
 */
extern tmg_handle_t* TMG;
extern fw_io_entity_t LED[8];
extern fw_spim_base_t FW_SPI0;
extern fw_spim_xfer_t FW_SPI0_XFER;
extern void terminal_write(void* str, uint32_t len);
extern char terminal_cache[256];
extern void scanner_scan(void);
/*-----------------------------------------------------------------------------------------
 *    Local Type/Structure
 */

/*-----------------------------------------------------------------------------------------
 *    Local Variable
 */


/*-----------------------------------------------------------------------------------------
 *    inline Function
 */
 
/*-----------------------------------------------------------------------------------------
 *    Public Function
 */
void delay(uint32_t us){
	uint32_t i;
	for(i=0; i<=us; i++){
		__NOP();
		__NOP();
		__NOP();
		__NOP();
	}
}

void loop(){
	int i, j;
	GPIO->SET[1] = 8;
	delay(1000000);
	GPIO->CLR[1] = 8;
	delay(1000000);
	LOGOUT("Start\n");
	scanner_scan();
	LOGOUT("Finish\n");
	while(1){
		GPIO->NOT[1] = 32;
		delay(1000000);
	}
}
/*-----------------------------------------------------------------------------------------
 *    End of file
 */

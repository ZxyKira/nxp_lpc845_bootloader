/*-----------------------------------------------------------------------------------------
 *    File Name   :start.c
 *    Version     :V1.0.0
 *    Create Date :2020-10-06
 *    Modufy Date :2020-10-06
 *    Information :
 */
#include <stdint.h>
#include "fw_chip.h"

/*-----------------------------------------------------------------------------------------
 *    Parameter
 */
 
/*-----------------------------------------------------------------------------------------
 *    Extern Function/Variable
 */
extern void external_io_startup(void);
extern void periph_io_startup(void);
extern void scanner_startup(void);

/*-----------------------------------------------------------------------------------------
 *    Local Type/Structure
 */

/*-----------------------------------------------------------------------------------------
 *    Local Variable
 */


/*-----------------------------------------------------------------------------------------
 *    Inline Function
 */
 
/*-----------------------------------------------------------------------------------------
 *    Local Function
 */ 
void start_hw(){
	fw_io_api.init(0);
	
	fw_spim_api.init(0);
	fw_spim_api.init(1);
	
	fw_usart_api.init(0);
}

/*-----------------------------------------------------------------------------------------
 *    Public Function
 */ 

void start(){
	fw_chip_init();
	start_hw();
	
	periph_io_startup();
	external_io_startup();
	scanner_startup();
}

/*****************************************************************************
 *	End of file
 */

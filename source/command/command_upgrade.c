/*-----------------------------------------------------------------------------------------
 *    File Name   :command_upgrade.c
 *    Version     :V1.0.0
 *    Create Date :2020-10-15
 *    Modufy Date :2020-10-15
 *    upgradermation :
 */
#include "terminal_entity.h"
#include <string.h>
#include <stdlib.h>
#include "FlashFaimPrg.h"

/*-----------------------------------------------------------------------------------------
 *    Parameter
 */

/*-----------------------------------------------------------------------------------------
 *    Extern Function/Variable
 */
extern void BootJump(uint32_t *Address);
/*-----------------------------------------------------------------------------------------
 *    Local Type/Structure
 */

/*-----------------------------------------------------------------------------------------
 *    Local Variable
 */
const char command_upgrade_text_cmd[] = "upgrade";
const char ASCII_ACK = 0x06;
const char ASCII_EOT = 0x04;
uint8_t upgrade_data[1024];
/*-----------------------------------------------------------------------------------------
 *    Variable
 */

/*-----------------------------------------------------------------------------------------
 *    Inline Function
 */
 
/*-----------------------------------------------------------------------------------------
 *    Local Function
 */

static void command_upfrade_writeFlash(void* ptr, uint32_t numb){
	uint32_t addr = 0x00008000;
	addr += (0x400 * numb);
	EraseSector(addr);
	Program(addr, 1024, ptr);
}

static void command_upgrade_loadData(terminal_xfer_api_t *pApi, uint32_t numb){
	int i;
	
	for(i=0; i<numb; i++){
		pApi->putCh(ASCII_ACK);
		pApi->read(&upgrade_data[0], 1024);
		command_upfrade_writeFlash(&upgrade_data[0], i);
	}
	pApi->putCh(ASCII_EOT);
	
}

static bool command_upgrade_handle(terminal_xfer_api_t *pApi, void* userData, int argc, char **argv){
	if(argc >= 2){
		uint32_t cnt = atoi(argv[1]);
		if(cnt == 0){
			pApi->sendString("upgrade packges number cannot be 0");
		}else{
			command_upgrade_loadData(pApi, cnt);
			pApi->sendString("upgrade finish");
			BootJump((uint32_t*)0x00008000);
		}
	}
	else{
			pApi->sendString("unknown param");
	}
	return true;
}

/*-----------------------------------------------------------------------------------------
 *    Public Function
 */
terminal_command_t command_upgrade_getCommand(){
	terminal_command_t command = {
		.command = command_upgrade_text_cmd,
		.userData = (void*)0x00000000,
		.handle = command_upgrade_handle,
	};	
	return command;
}

/*-----------------------------------------------------------------------------------------
 *    End of file
 */


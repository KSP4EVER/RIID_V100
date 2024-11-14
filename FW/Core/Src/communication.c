/*
 * communication.c
 *
 *  Created on: Nov 14, 2024
 *      Author: Misi
 */

#include "communication.h"


uint32_t PrintToBuffer(uint16_t data[],uint16_t size){
	uint32_t index = 0;
	for (uint32_t i = 0;i < size;i++){
		index = index + sprintf(UserTxBufferFS + index,"%d:%d\r\n",i, data[i]);
	}
	return index;
}

void StartVCPTransmission(uint32_t bytes_to_transmit){
	UserTxBufPtrOut = 0;
	UserTxBufPtrIn = bytes_to_transmit;
	Start_Transmit();

}

uint8_t IsVCPBusy(void){
	if (UserTxBufPtrOut != 0) return VCP_BUSY;
	else return VCP_RDY;
}


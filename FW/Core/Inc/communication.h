/*
 * communication.h
 *
 *  Created on: Nov 14, 2024
 *      Author: Misi
 */

#ifndef INC_COMMUNICATION_H_
#define INC_COMMUNICATION_H_

#define SEND_MSG_INTERVAL_MS 10000

#include "main.h"


extern uint8_t UserTxBufferFS[48*1024];

extern uint32_t UserTxBufPtrIn;
extern uint32_t UserTxBufPtrOut;

enum com_state{
	VCP_OK,
	VCP_RDY,
	VCP_BUSY
};

uint32_t PrintToBuffer(uint16_t data[],uint16_t size);
void StartVCPTransmission(uint32_t bytes_to_transmit);

#endif /* INC_COMMUNICATION_H_ */

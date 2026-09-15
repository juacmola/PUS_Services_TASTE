/*
 * cdtcdescriptor.c
 *
 *  Created on: Oct 7, 2024
 *      Author: opolo70
 */


#include "../include/public/cdtcmemdescriptor.h"
#include "../../../../llsw/sc_channel_drv/include/public/sc_channel_drv_v1.h"

	bool CDTCMemDescriptor::HandleIRQ(){

		return SC_Channel_RxData();

	}



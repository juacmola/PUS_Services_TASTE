/*
 * pus_services_iface_v1.h
 *
 *  Created on: Oct 26, 2024
 *      Author: Oscar Rodriguez Polo
 */

/****************************************************************************
 *
 *   This program is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU General Public License
 *   as published by the Free Software Foundation; either version 2
 *   of the License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,USA.
 *
 *
 ****************************************************************************/


#ifndef PUBLIC__ICUASW_PUS_SERVICES_IFACE_V1_H
#define PUBLIC__ICUASW_PUS_SERVICES_IFACE_V1_H


#include "../../../../llsw/config/include/public/config.h"
#include "../../../../llsw/config/include/public/basic_types.h"
//#include "../../../../llsw/rtmes_osswr/include/public/basic_types.h"
#include "../../../serialize/include/public/serialize.h"
#include "../../../../asw/dataclasses/CDTCHandler/include/public/cdtchandler_iface_v1.h"
#include "../../../../asw/dataclasses/CDTCMemDescriptor/include/public/cdtcmemdescriptor_iface_v1.h"


#include "../../../../llsw/tc_rate_ctrl/include/public/tc_rate_ctrl.h"

#include "../../pus_service01/include/public/pus_service01.h"
#include "../../pus_service02/include/public/pus_service02.h"
#include "../../pus_service03/include/public/pus_service03.h"
#include "../../pus_service17/include/public/pus_service17.h"
#include "../../pus_service20/include/public/pus_service20.h"
#include "../../pus_service05/include/public/pus_service05.h"
#include "../../pus_service12/include/public/pus_service12.h"
#include "../../pus_service19/include/public/pus_service19.h"

#ifdef __cplusplus
extern "C" {
#endif

//Start up
void pus_services_startup(void * irq_interface);

//Reboot
void pus_services_mng_reboot();


//Do FDIR
void pus_services_do_FDIR();

//Update Params
void pus_services_update_params();

#ifdef __cplusplus
}
#endif
#endif // PUBLIC__ICUASW_PUS_SERVICES_IFACE_V1_H

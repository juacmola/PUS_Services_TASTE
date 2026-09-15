/*
 * icuasw_pus_service1.cpp
 *
 *  Created on: Oct 21, 2024
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



#include "../../pus_service01/include/public/pus_service01.h"
#include "../include/public/pus_service17.h"
#include "../../../ccsds_pus/include/public/ccsds_pus.h"
#include "../../../crc/include/public/crc.h"

#include "../../pus_tm_handler/include/public/pus_tm_handler.h"

#include "../include/pus_service17/aux_pus_service17_exec_tc.h"

void pus_service17_exec_tc(
		tc_handler_t *ptc_handler){
	switch (ptc_handler->tc_df_header.subtype) {

	//TODO 08 execute pus_service17_exec_TC_17_1
		case (1):
				pus_service17_exec_TC_17_1(ptc_handler);
		break;
	default:
		//No defined code for this TC. ASW design error
		pus_service1_tx_TM_1_4_TC_X_Y_NO_EXEC_CODE(ptc_handler);

		break;
	}

}

void pus_service17_exec_TC_17_1(tc_handler_t *ptc_handler){


	//TODO 09 Tx TM[1,3]
	pus_service1_tx_TM_1_3(ptc_handler);

	//TODO 10 Tx TM[17,1]
	pus_service17_tx_TM_17_2(ptc_handler);

	//TODO 11 Tx TM[1,7]
	pus_service1_tx_TM_1_7(ptc_handler);


	//free memory
	tc_handler_free_memory(ptc_handler);
}



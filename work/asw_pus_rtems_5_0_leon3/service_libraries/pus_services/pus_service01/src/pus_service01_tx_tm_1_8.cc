/*
 * pus_service_1_4_tc_x_x.c
 *
 *  Created on: Oct 25, 2024
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

#include "../include/public/pus_service01.h"
#include "../include/pus_service01/aux_pus_service01_x_utils.h"
#include "../../../ccsds_pus/include/public/ccsds_pus.h"
#include "../../../crc/include/public/crc.h"
#include "../../../../llsw/tmtc_dyn_mem/include/public/tmtc_dyn_mem.h"
#include "../../pus_tc_handler/include/public/pus_tc_handler.h"
#include "../../pus_tm_handler/include/public/pus_tm_handler.h"




error_code_t pus_service1_tx_TM_1_8_Max_EvActions_defined(
		tc_handler_t *ptc_handler, uint16_t EvID) {

	return (pus_service1_tx_TM_1_X_uint16_failure_data(ptc_handler,
			TCVerifStageExecCompletion, TM_1_8_TC_19_1_MAX_EV_ACTIONS_REACHED,
			EvID));
}

error_code_t pus_service1_tx_TM_1_8_exceed_limit_appdata(
		tc_handler_t *ptc_handler) {

	return (pus_service1_tx_TM_1_X_no_failure_data(ptc_handler,
			TCVerifStageExecCompletion, TM_1_8_TM_X_Y_TM_EXCEED_LIMIT_APPDATA));

}

error_code_t pus_service1_tx_TM_1_8_dev_comman_exec_error(
		tc_handler_t *ptc_handler, uint32_t on_off_command) {

	return (pus_service1_tx_TM_1_X_uint32_failure_data(ptc_handler,
			TCVerifStageExecCompletion, TM_1_8_TM_2_1_DEV_COMMAND_EXEC_ERROR,
			on_off_command));

}

error_code_t pus_service1_tx_TM_1_8_not_free_stats_config(
		tc_handler_t *ptc_handler, uint16_t PID) {

	return (pus_service1_tx_TM_1_X_uint16_failure_data(ptc_handler,
			TCVerifStageExecCompletion,
			TM_1_8_TC_4_1_NOT_FREE_PID_STATS_CONFIG, PID));
}

error_code_t pus_service1_tx_TM_1_8_PID_stats_undefined(
		tc_handler_t *ptc_handler, uint16_t PID) {

	return (pus_service1_tx_TM_1_X_uint16_failure_data(ptc_handler,
			TCVerifStageExecStart, TM_1_8_TC_4_7_PID_STATS_UNDEFINED, PID));
}


error_code_t pus_service1_tx_TM_1_8_mem_access_error(tc_handler_t *ptc_handler,
		uint8_t MemID){

	return (pus_service1_tx_TM_1_X_uint8_failure_data(ptc_handler,
				TCVerifStageExecCompletion,
				TM_1_8_TC_6_X_MEM_ACCESS_FAIL, MemID));

}

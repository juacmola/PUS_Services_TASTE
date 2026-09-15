/*
 * emu_tc_programming.cpp
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

#include "../../../llsw/emu_hw_timecode_drv/include/public/emu_hw_timecode_drv_v1.h"
#include "../../../llsw/emu_sc_channel_drv/include/public/emu_sc_channel_drv_v1.h"
#include "../../../llsw/emu_gss/include/public/emu_gss_v1.h"

#define OBT_START_FT_ST20 (OBT_AFTER_POWER_ON + 0)

#define FT_UAH_ASW_ICU_ST20_SET_GET_PARAM_0070

#ifdef FT_UAH_ASW_ICU_ST20_SET_GET_PARAM_0070

#define FT_0070_TIME_step0 (OBT_START_FT_ST20 + 10)
#define FT_0070_TIME_step1 (OBT_START_FT_ST20 + 15)



//TODO Step 0  FT_UAH_ASW_ICU_ST20_SET_GET_PARAM_0070 step 0, Update PID 15 to 99
EmuGSS_TCProgram20_3_uint8 prog_FT_0070_step_0(FT_0070_TIME_step0,
		"FT_UAH_ASW_ICU_ST20_SET_GET_PARAM_0070 step 3, Update PID 15 to 99", 15, 99);

//TODO Step 1  FT_UAH_ASW_ICU_ST20_SET_GET_PARAM_0070 step 1, Update PID 15 to 99
EmuGSS_TCProgram20_1     prog_FT_0070_step_1(FT_0070_TIME_step1,
		"FT_UAH_ASW_ICU_ST20_SET_GET_PARAM_0070 step 4, Get PID 15", 15);

#endif

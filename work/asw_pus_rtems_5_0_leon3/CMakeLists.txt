cmake_minimum_required(VERSION 3.28)

project(MiBiblioteca LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(rtems_5_0_leon3 STATIC
	llsw/tc_queue_drv/src/tc_queue_drv.cc
	llsw/emu_gss/src/emu_gss.cc
	llsw/emu_gss/src/emu_gss_pus_service03.cc
	llsw/emu_gss/src/emu_gss_pus_service01.cc
	llsw/emu_gss/src/emu_gss_pus_service12.cc
	llsw/emu_gss/src/emu_gss_tm_handler.cc
	llsw/emu_gss/src/emu_gss_pus_service05.cc
	llsw/emu_gss/src/emu_gss_tc_program.cc
	llsw/emu_gss/src/emu_gss_pus_service02.cc
	llsw/emu_gss/src/emu_gss_pus_service20.cc
	llsw/emu_gss/src/emu_gss_pus_service17.cc
	llsw/emu_gss/src/emu_gss_pus_service19.cc
	llsw/emu_gss/src/emu_gss_sys_data_pool.cc
	llsw/tmtc_dyn_mem/src/tmtc_pool.cc
	llsw/tc_rate_ctrl/src/tc_rate_ctrl.cc
	llsw/emu_sc_channel_drv/src/emu_sc_channel_drv.cc
	llsw/emu_hw_timecode_drv/src/emu_hw_timecode_drv.cc
	asw/edroom_glue/src/edroomdeployment.cc
	asw/dataclasses/CDEvAction/src/cdevaction.cc
	asw/dataclasses/CDTCHandler/src/cdtchandler.cc
	asw/dataclasses/CDTCMemDescriptor/src/cdtcmemdescriptor.cc
	asw/components/uah_asw/src/UAH_ASWS.cc
	asw/components/uah_asw/src/UAH_ASWB.cc
	asw/components/cctcmanager/src/CCTCManagerB.cc
	asw/components/cctcmanager/src/CCTCManagerS.cc
	service_libraries/emu_tc_programming/src/emu_tc_programming_st20.cc
	service_libraries/emu_tc_programming/src/emu_tc_programming_st01_st17.cc
	service_libraries/emu_tc_programming/src/emu_tc_programming_st19.cc
	service_libraries/emu_tc_programming/src/emu_tc_programming_FDIR.cc
	service_libraries/emu_tc_programming/src/emu_tc_programming_st03.cc
	service_libraries/edroomsl/edroomsl_types/src/edroomsl_types.cc
	service_libraries/edroomsl/edroomsl/src/edroomtc.cc
	service_libraries/edroomsl/edroomsl/src/edroomsl.cc
)

target_include_directories(rtems_5_0_leon3
	PUBLIC
		${PROJECT_SOURCE_DIR}/llsw/config/include
		${PROJECT_SOURCE_DIR}/llsw/tc_queue_drv/include
		${PROJECT_SOURCE_DIR}/llsw/rtems_osswr/include
		${PROJECT_SOURCE_DIR}/llsw/rtems_osswr/include/rtems_osswr
		${PROJECT_SOURCE_DIR}/llsw/rtems_osswr/include
		${PROJECT_SOURCE_DIR}/llsw/emu_gss/include
		${PROJECT_SOURCE_DIR}/llsw/emu_gss/include
		${PROJECT_SOURCE_DIR}/llsw/tmtc_dyn_mem/include/tmtc_dyn_mem
		${PROJECT_SOURCE_DIR}/llsw/tmtc_dyn_mem/include
		${PROJECT_SOURCE_DIR}/llsw/emu_watchdog_drv/include
		${PROJECT_SOURCE_DIR}/llsw/sc_channel_drv/include
		${PROJECT_SOURCE_DIR}/llsw/tc_rate_ctrl/include
		${PROJECT_SOURCE_DIR}/llsw/device_drv/include
		${PROJECT_SOURCE_DIR}/llsw/emu_sc_channel_drv/include
		${PROJECT_SOURCE_DIR}/llsw/emu_hw_timecode_drv/include
		${PROJECT_SOURCE_DIR}/llsw/obt_drv/include
		${PROJECT_SOURCE_DIR}/llsw/emu_adc_drv/include
		${PROJECT_SOURCE_DIR}/asw/edroom_glue/include
		${PROJECT_SOURCE_DIR}/asw/edroom_glue/include
		${PROJECT_SOURCE_DIR}/asw/dataclasses/CDEvAction/include
		${PROJECT_SOURCE_DIR}/asw/dataclasses/CDTCAcceptReport/include
		${PROJECT_SOURCE_DIR}/asw/dataclasses/CDTCHandler/include
		${PROJECT_SOURCE_DIR}/asw/dataclasses/CDTCExecCtrl/include
		${PROJECT_SOURCE_DIR}/asw/dataclasses/CDTCMemDescriptor/include
		${PROJECT_SOURCE_DIR}/asw/components/uah_asw/include
		${PROJECT_SOURCE_DIR}/asw/components/cctcmanager/include
		${PROJECT_SOURCE_DIR}/service_libraries/pus_services/pus_service01/include/pus_service01
		${PROJECT_SOURCE_DIR}/service_libraries/pus_services/pus_service01/include
		${PROJECT_SOURCE_DIR}/service_libraries/pus_services/pus_service05/include/pus_service05
		${PROJECT_SOURCE_DIR}/service_libraries/pus_services/pus_service05/include
		${PROJECT_SOURCE_DIR}/service_libraries/pus_services/pus_sys_data_pool/include
		${PROJECT_SOURCE_DIR}/service_libraries/pus_services/pus_tc_handler/include
		${PROJECT_SOURCE_DIR}/service_libraries/pus_services/pus_service12/include/pus_service12
		${PROJECT_SOURCE_DIR}/service_libraries/pus_services/pus_service12/include
		${PROJECT_SOURCE_DIR}/service_libraries/pus_services/pus_tc_accept_report/include
		${PROJECT_SOURCE_DIR}/service_libraries/pus_services/include/pus_services
		${PROJECT_SOURCE_DIR}/service_libraries/pus_services/include
		${PROJECT_SOURCE_DIR}/service_libraries/pus_services/pus_service20/include/pus_service20
		${PROJECT_SOURCE_DIR}/service_libraries/pus_services/pus_service20/include
		${PROJECT_SOURCE_DIR}/service_libraries/pus_services/pus_tm_handler/include
		${PROJECT_SOURCE_DIR}/service_libraries/pus_services/pus_service19/include/pus_service19
		${PROJECT_SOURCE_DIR}/service_libraries/pus_services/pus_service19/include
		${PROJECT_SOURCE_DIR}/service_libraries/pus_services/pus_service03/include
		${PROJECT_SOURCE_DIR}/service_libraries/pus_services/pus_service03/include/pus_service03
		${PROJECT_SOURCE_DIR}/service_libraries/pus_services/pus_service17/include
		${PROJECT_SOURCE_DIR}/service_libraries/pus_services/pus_service17/include/pus_service17
		${PROJECT_SOURCE_DIR}/service_libraries/pus_services/pus_service02/include
		${PROJECT_SOURCE_DIR}/service_libraries/ccsds_pus/include/ccsds_pus
		${PROJECT_SOURCE_DIR}/service_libraries/ccsds_pus/include
		${PROJECT_SOURCE_DIR}/service_libraries/serialize/include
		${PROJECT_SOURCE_DIR}/service_libraries/crc/include
		${PROJECT_SOURCE_DIR}/service_libraries/edroomsl/edroomsl_types/include/edroomsl_types
		${PROJECT_SOURCE_DIR}/service_libraries/edroomsl/edroomsl_types/include
		${PROJECT_SOURCE_DIR}/service_libraries/edroomsl/edroombp/include/edroombp_swr
		${PROJECT_SOURCE_DIR}/service_libraries/edroomsl/edroombp/include/edroombp_swr/rtemsapi_5_1/rtems_5_1/leon3
		${PROJECT_SOURCE_DIR}/service_libraries/edroomsl/edroombp/include/edroombp_swr/rtemsapi_5_1/rtems_5_1
		${PROJECT_SOURCE_DIR}/service_libraries/edroomsl/edroombp/include
		${PROJECT_SOURCE_DIR}/service_libraries/edroomsl/edroomsl/include
		${PROJECT_SOURCE_DIR}/service_libraries/edroomsl/edroomsl/include/edroomsl
)


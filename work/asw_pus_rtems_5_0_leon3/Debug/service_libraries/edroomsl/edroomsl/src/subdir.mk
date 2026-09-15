################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../service_libraries/edroomsl/edroomsl/src/edroomsl.cpp \
../service_libraries/edroomsl/edroomsl/src/edroomtc.cpp 

CPP_DEPS += \
./service_libraries/edroomsl/edroomsl/src/edroomsl.d \
./service_libraries/edroomsl/edroomsl/src/edroomtc.d 

OBJS += \
./service_libraries/edroomsl/edroomsl/src/edroomsl.o \
./service_libraries/edroomsl/edroomsl/src/edroomtc.o 


# Each subdirectory must supply rules for building sources it contributes
service_libraries/edroomsl/edroomsl/src/%.o: ../service_libraries/edroomsl/edroomsl/src/%.cpp service_libraries/edroomsl/edroomsl/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	sparc-gaisler-rtems5-g++ -I/opt/rcc-1.3.2-gcc/sparc-gaisler-rtems5/leon3/lib/include -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/llsw/emu_watchdog_drv/include" -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/llsw/device_drv/include" -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/asw/components/uah_asw/include" -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/asw/components/cctcmanager/include" -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/asw/edroom_glue/include" -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/asw/dataclasses/CDTCExecCtrl/include" -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/asw/dataclasses/CDTCAcceptReport/include" -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/asw/dataclasses/CDTCMemDescriptor/include" -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/asw/dataclasses/CDEvAction/include" -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/asw/dataclasses/CDTCHandler/include" -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/service_libraries/pus_services/pus_sys_data_pool/include" -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/service_libraries/pus_services/pus_service03/include" -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/service_libraries/pus_services/pus_tm_handler/include" -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/service_libraries/pus_services/pus_service17/include" -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/service_libraries/pus_services/pus_service01/include" -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/service_libraries/pus_services/pus_tc_handler/include" -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/service_libraries/pus_services/pus_tc_accept_report/include" -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/service_libraries/pus_services/include" -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/service_libraries/crc/include" -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/service_libraries/ccsds_pus/include" -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/service_libraries/serialize/include" -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/service_libraries/edroomsl/edroombp/include" -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/service_libraries/edroomsl/edroomsl/include" -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/service_libraries/edroomsl/edroomsl_types/include" -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/llsw/emu_gss/include" -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/llsw/emu_adc_drv/include" -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/llsw/emu_hw_timecode_drv/include" -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/llsw/tc_rate_ctrl/include" -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/llsw/tc_queue_drv/include" -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/llsw/config/include" -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/llsw/obt_drv/include" -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/llsw/sc_channel_drv/include" -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/llsw/emu_sc_channel_drv/include" -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/llsw/tmtc_dyn_mem/include" -I"/home/atcsol/SCTRE_2026-workspace/asw_pus_rtems_5_0_leon3_st03/llsw/rtems_osswr/include" -O0 -g3 -Wall -c -fmessage-length=0 -mcpu=leon3 -qbsp=leon3 -msoft-float -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-service_libraries-2f-edroomsl-2f-edroomsl-2f-src

clean-service_libraries-2f-edroomsl-2f-edroomsl-2f-src:
	-$(RM) ./service_libraries/edroomsl/edroomsl/src/edroomsl.d ./service_libraries/edroomsl/edroomsl/src/edroomsl.o ./service_libraries/edroomsl/edroomsl/src/edroomtc.d ./service_libraries/edroomsl/edroomsl/src/edroomtc.o

.PHONY: clean-service_libraries-2f-edroomsl-2f-edroomsl-2f-src


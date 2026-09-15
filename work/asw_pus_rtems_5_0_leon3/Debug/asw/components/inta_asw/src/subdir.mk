################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../asw/components/inta_asw/src/INTA_ASWB.cpp \
../asw/components/inta_asw/src/INTA_ASWS.cpp 

CPP_DEPS += \
./asw/components/inta_asw/src/INTA_ASWB.d \
./asw/components/inta_asw/src/INTA_ASWS.d 

OBJS += \
./asw/components/inta_asw/src/INTA_ASWB.o \
./asw/components/inta_asw/src/INTA_ASWS.o 


# Each subdirectory must supply rules for building sources it contributes
asw/components/inta_asw/src/%.o: ../asw/components/inta_asw/src/%.cpp asw/components/inta_asw/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	sparc-gaisler-rtems5-g++ -I/opt/rcc-1.3.2-gcc/sparc-gaisler-rtems5/leon3/lib/include -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/llsw/leon3_uart_drv/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/asw/components/cchk_fdirmng/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/service_libraries/pus_services/pus_service09/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/service_libraries/pus_services/pus_service128/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/llsw/emu_watchdog_drv/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/service_libraries/pus_services/pus_service06/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/service_libraries/pus_services/pus_service04/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/llsw/device_drv/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/service_libraries/pus_services/pus_service02/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/asw/components/ccbkgtcexec/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/asw/components/inta_asw/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/asw/components/cctcmanager/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/asw/edroom_glue/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/asw/dataclasses/CDTCExecCtrl/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/asw/dataclasses/CDTCAcceptReport/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/asw/dataclasses/CDTCMemDescriptor/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/asw/dataclasses/CDEvAction/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/asw/dataclasses/CDTCHandler/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/service_libraries/pus_services/pus_service19/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/service_libraries/pus_services/pus_service12/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/service_libraries/pus_services/pus_service20/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/service_libraries/pus_services/pus_service05/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/service_libraries/pus_services/pus_sys_data_pool/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/service_libraries/pus_services/pus_service03/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/service_libraries/pus_services/pus_tm_handler/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/service_libraries/pus_services/pus_service17/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/service_libraries/pus_services/pus_service01/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/service_libraries/pus_services/pus_tc_handler/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/service_libraries/pus_services/pus_tc_accept_report/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/service_libraries/pus_services/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/service_libraries/crc/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/service_libraries/ccsds_pus/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/service_libraries/serialize/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/service_libraries/edroomsl/edroombp/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/service_libraries/edroomsl/edroomsl/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/service_libraries/edroomsl/edroomsl_types/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/llsw/emu_adc_drv/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/llsw/emu_hw_timecode_drv/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/llsw/tc_rate_ctrl/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/llsw/tc_queue_drv/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/llsw/config/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/llsw/obt_drv/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/llsw/sc_channel_drv/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/llsw/tmtc_dyn_mem/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_massiva/llsw/rtems_osswr/include" -O0 -g3 -Wall -c -fmessage-length=0 -mcpu=leon3 -qbsp=leon3 -msoft-float -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-asw-2f-components-2f-inta_asw-2f-src

clean-asw-2f-components-2f-inta_asw-2f-src:
	-$(RM) ./asw/components/inta_asw/src/INTA_ASWB.d ./asw/components/inta_asw/src/INTA_ASWB.o ./asw/components/inta_asw/src/INTA_ASWS.d ./asw/components/inta_asw/src/INTA_ASWS.o

.PHONY: clean-asw-2f-components-2f-inta_asw-2f-src


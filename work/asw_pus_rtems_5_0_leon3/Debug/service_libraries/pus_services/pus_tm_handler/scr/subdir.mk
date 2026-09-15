################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../service_libraries/pus_services/pus_tm_handler/scr/pus_tm_handler.c 

C_DEPS += \
./service_libraries/pus_services/pus_tm_handler/scr/pus_tm_handler.d 

OBJS += \
./service_libraries/pus_services/pus_tm_handler/scr/pus_tm_handler.o 


# Each subdirectory must supply rules for building sources it contributes
service_libraries/pus_services/pus_tm_handler/scr/%.o: ../service_libraries/pus_services/pus_tm_handler/scr/%.c service_libraries/pus_services/pus_tm_handler/scr/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	sparc-gaisler-rtems5-gcc -std=c99 -I/opt/rcc-1.3.2-gcc/sparc-gaisler-rtems5/leon3/lib/include -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_all/asw/edroom_glue/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_all/service_libraries/pus_services/pus_service09/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_all/service_libraries/pus_services/pus_service128/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_all/llsw/emu_watchdog_drv/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_all/service_libraries/pus_services/pus_service06/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_all/service_libraries/pus_services/pus_service04/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_all/llsw/device_drv/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_all/service_libraries/pus_services/pus_service02/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_all/service_libraries/pus_services/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_all/service_libraries/pus_services/pus_sys_data_pool/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_all/service_libraries/pus_services/pus_service19/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_all/service_libraries/pus_services/pus_service12/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_all/service_libraries/pus_services/pus_service20/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_all/service_libraries/pus_services/pus_service05/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_all/service_libraries/pus_services/pus_service03/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_all/service_libraries/pus_services/pus_tm_handler/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_all/service_libraries/pus_services/pus_service01/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_all/service_libraries/pus_services/pus_service17/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_all/service_libraries/pus_services/pus_tm_handler/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_all/service_libraries/pus_services/pus_tc_handler/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_all/service_libraries/pus_services/pus_tc_accept_report/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_all/service_libraries/crc/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_all/service_libraries/edroomsl/edroombp/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_all/service_libraries/ccsds_pus/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_all/service_libraries/serialize/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_all/llsw/obt_drv/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_all/llsw/emu_hw_timecode_drv/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_all/llsw/emu_adc_drv/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_all/llsw/emu_gss/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_all/llsw/tmtc_dyn_mem/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_all/llsw/config/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_all/llsw/emu_sc_channel_drv/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_all/llsw/sc_channel_drv/include" -I"/home/opolo70/CAN-workspace/asw_isdefe_pus_rtems_5_0_leon3_all/llsw/rtems_osswr/include" -O0 -g3 -Wall -c -fmessage-length=0 -mcpu=leon3 -qbsp=leon3 -msoft-float -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-service_libraries-2f-pus_services-2f-pus_tm_handler-2f-scr

clean-service_libraries-2f-pus_services-2f-pus_tm_handler-2f-scr:
	-$(RM) ./service_libraries/pus_services/pus_tm_handler/scr/pus_tm_handler.d ./service_libraries/pus_services/pus_tm_handler/scr/pus_tm_handler.o

.PHONY: clean-service_libraries-2f-pus_services-2f-pus_tm_handler-2f-scr


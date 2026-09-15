################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../service_libraries/edroomsl/edroombp/src/rtemsapi_4_6/rtems_4_6/leon3/leon3_hw_irqs.c 

C_DEPS += \
./service_libraries/edroomsl/edroombp/src/rtemsapi_4_6/rtems_4_6/leon3/leon3_hw_irqs.d 

OBJS += \
./service_libraries/edroomsl/edroombp/src/rtemsapi_4_6/rtems_4_6/leon3/leon3_hw_irqs.o 


# Each subdirectory must supply rules for building sources it contributes
service_libraries/edroomsl/edroombp/src/rtemsapi_4_6/rtems_4_6/leon3/%.o: ../service_libraries/edroomsl/edroombp/src/rtemsapi_4_6/rtems_4_6/leon3/%.c service_libraries/edroomsl/edroombp/src/rtemsapi_4_6/rtems_4_6/leon3/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	sparc-gaisler-rtems5-gcc -std=c99 -I/opt/rcc-1.3.2-gcc/sparc-gaisler-rtems5/leon3/lib/include -I"/home/debian/eclipse-workspace/asw_isdefe_pus_rtems_leon3_all/asw/edroom_glue/include" -I"/home/debian/eclipse-workspace/asw_isdefe_pus_rtems_leon3_all/service_libraries/pus_services/pus_service09/include" -I"/home/debian/eclipse-workspace/asw_isdefe_pus_rtems_leon3_all/service_libraries/pus_services/pus_service128/include" -I"/home/debian/eclipse-workspace/asw_isdefe_pus_rtems_leon3_all/llsw/emu_watchdog_drv/include" -I"/home/debian/eclipse-workspace/asw_isdefe_pus_rtems_leon3_all/service_libraries/pus_services/pus_service06/include" -I"/home/debian/eclipse-workspace/asw_isdefe_pus_rtems_leon3_all/service_libraries/pus_services/pus_service04/include" -I"/home/debian/eclipse-workspace/asw_isdefe_pus_rtems_leon3_all/llsw/device_drv/include" -I"/home/debian/eclipse-workspace/asw_isdefe_pus_rtems_leon3_all/service_libraries/pus_services/pus_service02/include" -I"/home/debian/eclipse-workspace/asw_isdefe_pus_rtems_leon3_all/service_libraries/pus_services/include" -I"/home/debian/eclipse-workspace/asw_isdefe_pus_rtems_leon3_all/service_libraries/pus_services/pus_sys_data_pool/include" -I"/home/debian/eclipse-workspace/asw_isdefe_pus_rtems_leon3_all/service_libraries/pus_services/pus_service19/include" -I"/home/debian/eclipse-workspace/asw_isdefe_pus_rtems_leon3_all/service_libraries/pus_services/pus_service12/include" -I"/home/debian/eclipse-workspace/asw_isdefe_pus_rtems_leon3_all/service_libraries/pus_services/pus_service20/include" -I"/home/debian/eclipse-workspace/asw_isdefe_pus_rtems_leon3_all/service_libraries/pus_services/pus_service05/include" -I"/home/debian/eclipse-workspace/asw_isdefe_pus_rtems_leon3_all/service_libraries/pus_services/pus_service03/include" -I"/home/debian/eclipse-workspace/asw_isdefe_pus_rtems_leon3_all/service_libraries/pus_services/pus_tm_handler/include" -I"/home/debian/eclipse-workspace/asw_isdefe_pus_rtems_leon3_all/service_libraries/pus_services/pus_service01/include" -I"/home/debian/eclipse-workspace/asw_isdefe_pus_rtems_leon3_all/service_libraries/pus_services/pus_service17/include" -I"/home/debian/eclipse-workspace/asw_isdefe_pus_rtems_leon3_all/service_libraries/pus_services/pus_tm_handler/include" -I"/home/debian/eclipse-workspace/asw_isdefe_pus_rtems_leon3_all/service_libraries/pus_services/pus_tc_handler/include" -I"/home/debian/eclipse-workspace/asw_isdefe_pus_rtems_leon3_all/service_libraries/pus_services/pus_tc_accept_report/include" -I"/home/debian/eclipse-workspace/asw_isdefe_pus_rtems_leon3_all/service_libraries/crc/include" -I"/home/debian/eclipse-workspace/asw_isdefe_pus_rtems_leon3_all/service_libraries/edroomsl/edroombp/include" -I"/home/debian/eclipse-workspace/asw_isdefe_pus_rtems_leon3_all/service_libraries/ccsds_pus/include" -I"/home/debian/eclipse-workspace/asw_isdefe_pus_rtems_leon3_all/service_libraries/serialize/include" -I"/home/debian/eclipse-workspace/asw_isdefe_pus_rtems_leon3_all/llsw/obt_drv/include" -I"/home/debian/eclipse-workspace/asw_isdefe_pus_rtems_leon3_all/llsw/emu_hw_timecode_drv/include" -I"/home/debian/eclipse-workspace/asw_isdefe_pus_rtems_leon3_all/llsw/emu_adc_drv/include" -I"/home/debian/eclipse-workspace/asw_isdefe_pus_rtems_leon3_all/llsw/emu_gss/include" -I"/home/debian/eclipse-workspace/asw_isdefe_pus_rtems_leon3_all/llsw/tmtc_dyn_mem/include" -I"/home/debian/eclipse-workspace/asw_isdefe_pus_rtems_leon3_all/llsw/config/include" -I"/home/debian/eclipse-workspace/asw_isdefe_pus_rtems_leon3_all/llsw/emu_sc_channel_drv/include" -I"/home/debian/eclipse-workspace/asw_isdefe_pus_rtems_leon3_all/llsw/sc_channel_drv/include" -I"/home/debian/eclipse-workspace/asw_isdefe_pus_rtems_leon3_all/llsw/rtems_osswr/include" -O0 -g3 -Wall -c -fmessage-length=0 -mcpu=leon3 -qbsp=leon3 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-service_libraries-2f-edroomsl-2f-edroombp-2f-src-2f-rtemsapi_4_6-2f-rtems_4_6-2f-leon3

clean-service_libraries-2f-edroomsl-2f-edroombp-2f-src-2f-rtemsapi_4_6-2f-rtems_4_6-2f-leon3:
	-$(RM) ./service_libraries/edroomsl/edroombp/src/rtemsapi_4_6/rtems_4_6/leon3/leon3_hw_irqs.d ./service_libraries/edroomsl/edroombp/src/rtemsapi_4_6/rtems_4_6/leon3/leon3_hw_irqs.o

.PHONY: clean-service_libraries-2f-edroomsl-2f-edroombp-2f-src-2f-rtemsapi_4_6-2f-rtems_4_6-2f-leon3


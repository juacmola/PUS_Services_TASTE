################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../llsw/leon3_uart_drv/src/leon3_uart_drv.c 

C_DEPS += \
./llsw/leon3_uart_drv/src/leon3_uart_drv.d 

OBJS += \
./llsw/leon3_uart_drv/src/leon3_uart_drv.o 


# Each subdirectory must supply rules for building sources it contributes
llsw/leon3_uart_drv/src/%.o: ../llsw/leon3_uart_drv/src/%.c llsw/leon3_uart_drv/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	sparc-gaisler-rtems5-gcc -std=c99 -I/opt/rcc-1.3.2-gcc/sparc-gaisler-rtems5/leon3/lib/include -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/llsw/leon3_uart_drv/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/asw/edroom_glue/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/pus_service09/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/pus_service128/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/llsw/emu_watchdog_drv/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/pus_service06/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/pus_service04/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/llsw/device_drv/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/pus_service02/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/pus_sys_data_pool/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/pus_service19/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/pus_service12/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/pus_service20/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/pus_service05/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/pus_service03/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/pus_tm_handler/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/pus_service01/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/pus_service17/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/pus_tm_handler/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/pus_tc_handler/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/pus_tc_accept_report/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/crc/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/edroomsl/edroombp/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/ccsds_pus/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/serialize/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/llsw/obt_drv/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/llsw/emu_hw_timecode_drv/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/llsw/emu_adc_drv/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/llsw/tmtc_dyn_mem/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/llsw/config/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/llsw/sc_channel_drv/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/llsw/rtems_osswr/include" -O0 -g3 -Wall -c -fmessage-length=0 -mcpu=leon3 -qbsp=leon3 -msoft-float -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-llsw-2f-leon3_uart_drv-2f-src

clean-llsw-2f-leon3_uart_drv-2f-src:
	-$(RM) ./llsw/leon3_uart_drv/src/leon3_uart_drv.d ./llsw/leon3_uart_drv/src/leon3_uart_drv.o

.PHONY: clean-llsw-2f-leon3_uart_drv-2f-src


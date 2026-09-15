################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../service_libraries/pus_services/pus_service05/src/aux_pus_service05_exec_tc.c \
../service_libraries/pus_services/pus_service05/src/aux_pus_service05_tx_tm.c \
../service_libraries/pus_services/pus_service05/src/aux_pus_service05_utils.c \
../service_libraries/pus_services/pus_service05/src/pus_service05.c 

C_DEPS += \
./service_libraries/pus_services/pus_service05/src/aux_pus_service05_exec_tc.d \
./service_libraries/pus_services/pus_service05/src/aux_pus_service05_tx_tm.d \
./service_libraries/pus_services/pus_service05/src/aux_pus_service05_utils.d \
./service_libraries/pus_services/pus_service05/src/pus_service05.d 

OBJS += \
./service_libraries/pus_services/pus_service05/src/aux_pus_service05_exec_tc.o \
./service_libraries/pus_services/pus_service05/src/aux_pus_service05_tx_tm.o \
./service_libraries/pus_services/pus_service05/src/aux_pus_service05_utils.o \
./service_libraries/pus_services/pus_service05/src/pus_service05.o 


# Each subdirectory must supply rules for building sources it contributes
service_libraries/pus_services/pus_service05/src/%.o: ../service_libraries/pus_services/pus_service05/src/%.c service_libraries/pus_services/pus_service05/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	sparc-gaisler-rtems5-gcc -std=c99 -I/opt/rcc-1.3.2-gcc/sparc-gaisler-rtems5/leon3/lib/include -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/llsw/leon3_uart_drv/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/asw/edroom_glue/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/pus_service09/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/pus_service128/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/llsw/emu_watchdog_drv/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/pus_service06/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/pus_service04/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/llsw/device_drv/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/pus_service02/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/pus_sys_data_pool/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/pus_service19/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/pus_service12/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/pus_service20/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/pus_service05/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/pus_service03/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/pus_tm_handler/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/pus_service01/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/pus_service17/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/pus_tm_handler/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/pus_tc_handler/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/pus_services/pus_tc_accept_report/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/crc/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/edroomsl/edroombp/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/ccsds_pus/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/service_libraries/serialize/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/llsw/obt_drv/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/llsw/emu_hw_timecode_drv/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/llsw/emu_adc_drv/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/llsw/tmtc_dyn_mem/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/llsw/config/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/llsw/sc_channel_drv/include" -I"/home/opolo70/OBDH_2025-workspace/asw_pus_rtems_5_0_leon3_st01_st17/llsw/rtems_osswr/include" -O0 -g3 -Wall -c -fmessage-length=0 -mcpu=leon3 -qbsp=leon3 -msoft-float -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-service_libraries-2f-pus_services-2f-pus_service05-2f-src

clean-service_libraries-2f-pus_services-2f-pus_service05-2f-src:
	-$(RM) ./service_libraries/pus_services/pus_service05/src/aux_pus_service05_exec_tc.d ./service_libraries/pus_services/pus_service05/src/aux_pus_service05_exec_tc.o ./service_libraries/pus_services/pus_service05/src/aux_pus_service05_tx_tm.d ./service_libraries/pus_services/pus_service05/src/aux_pus_service05_tx_tm.o ./service_libraries/pus_services/pus_service05/src/aux_pus_service05_utils.d ./service_libraries/pus_services/pus_service05/src/aux_pus_service05_utils.o ./service_libraries/pus_services/pus_service05/src/pus_service05.d ./service_libraries/pus_services/pus_service05/src/pus_service05.o

.PHONY: clean-service_libraries-2f-pus_services-2f-pus_service05-2f-src


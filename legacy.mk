# Sources shared by the PUS library and the Linux TASTE deployment.
LEGACY_ROOT := $(abspath work/asw_pus_rtems_5_0_leon3)
LEGACY_DIRS := $(LEGACY_ROOT)/taste_linux $(wildcard $(LEGACY_ROOT)/llsw/emu_*/src) \
 $(LEGACY_ROOT)/llsw/tc_queue_drv/src \
 $(LEGACY_ROOT)/llsw/tc_rate_ctrl/src \
 $(LEGACY_ROOT)/llsw/tmtc_dyn_mem/src \
 $(LEGACY_ROOT)/llsw/device_drv/src \
 $(LEGACY_ROOT)/llsw/obt_drv/src \
 $(wildcard $(LEGACY_ROOT)/service_libraries/pus_services/*/src) \
 $(LEGACY_ROOT)/service_libraries/pus_services/src \
 $(LEGACY_ROOT)/service_libraries/ccsds_pus/src \
 $(LEGACY_ROOT)/service_libraries/serialize/src \
 $(LEGACY_ROOT)/service_libraries/crc/src \
 $(LEGACY_ROOT)/asw/dataclasses/CDTCHandler/src \
 $(LEGACY_ROOT)/asw/dataclasses/CDTCMemDescriptor/src \
 $(LEGACY_ROOT)/asw/dataclasses/CDEvAction/src
legacy_empty :=
legacy_space := $(legacy_empty) $(legacy_empty)
export DEMO_EXTERNAL_SOURCE_PATH := $(subst $(legacy_space),:,$(strip $(LEGACY_DIRS)))
export DEMO_USER_CFLAGS += -I$(LEGACY_ROOT)/llsw/config/include -I$(LEGACY_ROOT)/llsw/rtems_osswr/include

LEGACY_INCLUDES := $(wildcard $(LEGACY_ROOT)/llsw/*/include) $(wildcard $(LEGACY_ROOT)/service_libraries/*/include) $(wildcard $(LEGACY_ROOT)/service_libraries/pus_services/*/include)
export DEMO_USER_CFLAGS += $(addprefix -I,$(LEGACY_INCLUDES))

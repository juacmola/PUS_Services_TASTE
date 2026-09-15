// Select exactly one emu_tc_programming scenario before running TASTE.
// The selected file registers its programmed TCs through static objects.
#ifdef GENERIC_LINUX_TARGET
#include "public/emu_gss_v1.h"
#include "public/emu_hw_timecode_drv_v1.h"

// Change this one define when testing another service.
#define EMU_TC_PROGRAMMING_ST03

#if defined(EMU_TC_PROGRAMMING_ST03)
#include "../service_libraries/emu_tc_programming/src/emu_tc_programming_st03.cc"
#elif defined(EMU_TC_PROGRAMMING_ST01_ST17)
#include "../service_libraries/emu_tc_programming/src/emu_tc_programming_st01_st17.cc"
#elif defined(EMU_TC_PROGRAMMING_ST19)
#include "../service_libraries/emu_tc_programming/src/emu_tc_programming_st19.cc"
#elif defined(EMU_TC_PROGRAMMING_ST20)
#include "../service_libraries/emu_tc_programming/src/emu_tc_programming_st20.cc"
#elif defined(EMU_TC_PROGRAMMING_FDIR)
#include "../service_libraries/emu_tc_programming/src/emu_tc_programming_FDIR.cc"
#else
#error "Select one EMU_TC_PROGRAMMING_* scenario in gss_schedule.cc"
#endif

extern "C" void TasteGSS_InitSchedule() {}
#endif

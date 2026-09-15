// Implementation of the glue code in C handling required interfaces

#include "dataview-uniq.h" // Always required for the definition of the PID type
#include <stdlib.h>
#include <stdio.h>
#include "PrintTypesAsASN1.h"
#include "timeInMS.h"

static asn1SccT_Runtime_Error hkfdirmng_recent_error = { .kind = T_Runtime_Error_noerror_PRESENT };

extern unsigned hkfdirmng_initialized;

void hkfdirmng_RI_SEvAction_To_PID(asn1SccPID dest_pid);
void hkfdirmng_RI_SEvAction(void);
void hkfdirmng_RI_SEvAction(void)
{
   // When no destination is specified, send to everyone (multicast)
   hkfdirmng_RI_SEvAction_To_PID(PID_env);
}

void hkfdirmng_RI_SEvAction_To_PID(asn1SccPID dest_pid)
{
   // Log MSC data on Linux when environment variable is set
   static int innerMsc = -1;
   if (-1 == innerMsc)
      innerMsc = (NULL != getenv("TASTE_INNER_MSC"))?1:0;
   if (1 == innerMsc) {
      long long msc_time = getTimeInMilliseconds();
      // Log message to TCManager (corresponding PI: SEvAction)
      printf ("INNER_RI: hkfdirmng,tcmanager,sevaction,sevaction,%lld\n", msc_time);
      fflush(stdout);
   }


   // Send the message via the middleware API
   extern void vm_hkfdirmng_sevaction(asn1SccPID);
   vm_hkfdirmng_sevaction(dest_pid);

  hkfdirmng_recent_error.kind = T_Runtime_Error_noerror_PRESENT;
}

// Get the PID of the sender function. The actual function is defined in _vm_if.c
// as the sender PID is received together with incoming PI calls
void hkfdirmng_RI_get_sender(asn1SccPID *sender_pid)
{
  extern void hkfdirmng_get_sender(asn1SccPID *sender_pid);
  hkfdirmng_get_sender(sender_pid);
}

void hkfdirmng_RI_get_last_error(asn1SccT_Runtime_Error* err)
{
    *err = hkfdirmng_recent_error;
}

void hkfdirmng_get_last_error(asn1SccT_Runtime_Error* err, const asn1SccPID* dest)
{
    hkfdirmng_RI_get_last_error(err);
}


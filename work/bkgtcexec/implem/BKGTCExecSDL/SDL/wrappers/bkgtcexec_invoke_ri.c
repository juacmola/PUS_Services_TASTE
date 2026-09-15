// Implementation of the glue code in C handling required interfaces

#include "dataview-uniq.h" // Always required for the definition of the PID type
#include <stdlib.h>
#include <stdio.h>
#include "PrintTypesAsASN1.h"
#include "timeInMS.h"
#include "C_ASN1_Types.h"

static asn1SccT_Runtime_Error bkgtcexec_recent_error = { .kind = T_Runtime_Error_noerror_PRESENT };

extern unsigned bkgtcexec_initialized;

void bkgtcexec_RI_ExecBKGTC_To_PID(asn1SccPID dest_pid, 
      const asn1SccRawTC *IN_packet
);
void bkgtcexec_RI_ExecBKGTC(
      const asn1SccRawTC *IN_packet
);
void bkgtcexec_RI_ExecBKGTC(
      const asn1SccRawTC *IN_packet
)
{
   // When no destination is specified, send to everyone (multicast)
   bkgtcexec_RI_ExecBKGTC_To_PID(PID_env, IN_packet
);
}

void bkgtcexec_RI_ExecBKGTC_To_PID(asn1SccPID dest_pid, 
      const asn1SccRawTC *IN_packet
)
{
   // Log MSC data on Linux when environment variable is set
   static int innerMsc = -1;
   if (-1 == innerMsc)
      innerMsc = (NULL != getenv("TASTE_INNER_MSC"))?1:0;
   if (1 == innerMsc) {
      long long msc_time = getTimeInMilliseconds();
      // Log message to Legacy (corresponding PI: ExecBKGTC)
      printf ("INNER_RI: bkgtcexec,legacy,execbkgtc,execbkgtc,%lld\n", msc_time);
      fflush(stdout);
   }


   // Send the message via the middleware API
   extern void vm_bkgtcexec_execbkgtc
     (asn1SccPID,
      void *, size_t);

   vm_bkgtcexec_execbkgtc
     (dest_pid,
      (void *)IN_packet, sizeof(asn1SccRawTC));


  bkgtcexec_recent_error.kind = T_Runtime_Error_noerror_PRESENT;
}

// Get the PID of the sender function. The actual function is defined in _vm_if.c
// as the sender PID is received together with incoming PI calls
void bkgtcexec_RI_get_sender(asn1SccPID *sender_pid)
{
  extern void bkgtcexec_get_sender(asn1SccPID *sender_pid);
  bkgtcexec_get_sender(sender_pid);
}

void bkgtcexec_RI_get_last_error(asn1SccT_Runtime_Error* err)
{
    *err = bkgtcexec_recent_error;
}

void bkgtcexec_get_last_error(asn1SccT_Runtime_Error* err, const asn1SccPID* dest)
{
    bkgtcexec_RI_get_last_error(err);
}


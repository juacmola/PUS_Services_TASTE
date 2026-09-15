// Implementation of the glue code in C handling required interfaces

#include "dataview-uniq.h" // Always required for the definition of the PID type
#include <stdlib.h>
#include <stdio.h>
#include "PrintTypesAsASN1.h"
#include "timeInMS.h"
#include "C_ASN1_Types.h"

static asn1SccT_Runtime_Error tcmanager_recent_error = { .kind = T_Runtime_Error_noerror_PRESENT };

extern unsigned tcmanager_initialized;

void tcmanager_RI_HandleTC_To_PID(asn1SccPID dest_pid, 
      asn1SccFwdCommand *OUT_route,
       asn1SccRawTC      *OUT_packet
);
void tcmanager_RI_HandleTC(
      asn1SccFwdCommand *OUT_route,
       asn1SccRawTC      *OUT_packet
);
void tcmanager_RI_HandleTC(
      asn1SccFwdCommand *OUT_route,
       asn1SccRawTC      *OUT_packet
)
{
   // When no destination is specified, send to everyone (multicast)
   tcmanager_RI_HandleTC_To_PID(PID_env, OUT_route, OUT_packet
);
}

void tcmanager_RI_HandleTC_To_PID(asn1SccPID dest_pid, 
      asn1SccFwdCommand *OUT_route,
       asn1SccRawTC      *OUT_packet
)
{
   // Log MSC data on Linux when environment variable is set
   static int innerMsc = -1;
   if (-1 == innerMsc)
      innerMsc = (NULL != getenv("TASTE_INNER_MSC"))?1:0;
   if (1 == innerMsc) {
      long long msc_time = getTimeInMilliseconds();
      // Log message to Legacy (corresponding PI: HandleTC)
      printf ("INNER_RI: tcmanager,legacy,handletc,handletc,%lld\n", msc_time);
      fflush(stdout);
   }

   size_t      size_OUT_buf_route = 0;
   size_t      size_OUT_buf_packet = 0;

   // Send the message via the middleware API
   extern void vm_tcmanager_handletc
     (asn1SccPID,
      void *, size_t *,
      void *, size_t *);

   vm_tcmanager_handletc
     (dest_pid,
      (void *)OUT_route, &size_OUT_buf_route,
      (void *)OUT_packet, &size_OUT_buf_packet);


  tcmanager_recent_error.kind = T_Runtime_Error_noerror_PRESENT;
}



void tcmanager_RI_Init_To_PID(asn1SccPID dest_pid);
void tcmanager_RI_Init(void);
void tcmanager_RI_Init(void)
{
   // When no destination is specified, send to everyone (multicast)
   tcmanager_RI_Init_To_PID(PID_env);
}

void tcmanager_RI_Init_To_PID(asn1SccPID dest_pid)
{
   // Log MSC data on Linux when environment variable is set
   static int innerMsc = -1;
   if (-1 == innerMsc)
      innerMsc = (NULL != getenv("TASTE_INNER_MSC"))?1:0;
   if (1 == innerMsc) {
      long long msc_time = getTimeInMilliseconds();
      // Log message to Legacy (corresponding PI: Init)
      printf ("INNER_RI: tcmanager,legacy,init,init,%lld\n", msc_time);
      fflush(stdout);
   }


   // Send the message via the middleware API
   extern void vm_tcmanager_init(asn1SccPID);
   vm_tcmanager_init(dest_pid);

  tcmanager_recent_error.kind = T_Runtime_Error_noerror_PRESENT;
}



void tcmanager_RI_NewEvAction_To_PID(asn1SccPID dest_pid, 
      asn1SccRxTC *OUT_accepted
);
void tcmanager_RI_NewEvAction(
      asn1SccRxTC *OUT_accepted
);
void tcmanager_RI_NewEvAction(
      asn1SccRxTC *OUT_accepted
)
{
   // When no destination is specified, send to everyone (multicast)
   tcmanager_RI_NewEvAction_To_PID(PID_env, OUT_accepted
);
}

void tcmanager_RI_NewEvAction_To_PID(asn1SccPID dest_pid, 
      asn1SccRxTC *OUT_accepted
)
{
   // Log MSC data on Linux when environment variable is set
   static int innerMsc = -1;
   if (-1 == innerMsc)
      innerMsc = (NULL != getenv("TASTE_INNER_MSC"))?1:0;
   if (1 == innerMsc) {
      long long msc_time = getTimeInMilliseconds();
      // Log message to Legacy (corresponding PI: NewEvAction)
      printf ("INNER_RI: tcmanager,legacy,newevaction,newevaction,%lld\n", msc_time);
      fflush(stdout);
   }

   size_t      size_OUT_buf_accepted = 0;

   // Send the message via the middleware API
   extern void vm_tcmanager_newevaction
     (asn1SccPID,
      void *, size_t *);

   vm_tcmanager_newevaction
     (dest_pid,
      (void *)OUT_accepted, &size_OUT_buf_accepted);


  tcmanager_recent_error.kind = T_Runtime_Error_noerror_PRESENT;
}



void tcmanager_RI_NewRxTC_To_PID(asn1SccPID dest_pid, 
      const asn1SccTelecommand *IN_tc,
       asn1SccRxTC              *OUT_accepted
);
void tcmanager_RI_NewRxTC(
      const asn1SccTelecommand *IN_tc,
       asn1SccRxTC              *OUT_accepted
);
void tcmanager_RI_NewRxTC(
      const asn1SccTelecommand *IN_tc,
       asn1SccRxTC              *OUT_accepted
)
{
   // When no destination is specified, send to everyone (multicast)
   tcmanager_RI_NewRxTC_To_PID(PID_env, IN_tc, OUT_accepted
);
}

void tcmanager_RI_NewRxTC_To_PID(asn1SccPID dest_pid, 
      const asn1SccTelecommand *IN_tc,
       asn1SccRxTC              *OUT_accepted
)
{
   // Log MSC data on Linux when environment variable is set
   static int innerMsc = -1;
   if (-1 == innerMsc)
      innerMsc = (NULL != getenv("TASTE_INNER_MSC"))?1:0;
   if (1 == innerMsc) {
      long long msc_time = getTimeInMilliseconds();
      // Log message to Legacy (corresponding PI: NewRxTC)
      printf ("INNER_RI: tcmanager,legacy,newrxtc,newrxtc,%lld\n", msc_time);
      fflush(stdout);
   }

   size_t      size_OUT_buf_accepted = 0;

   // Send the message via the middleware API
   extern void vm_tcmanager_newrxtc
     (asn1SccPID,
      void *, size_t,
      void *, size_t *);

   vm_tcmanager_newrxtc
     (dest_pid,
      (void *)IN_tc, sizeof(asn1SccTelecommand),
      (void *)OUT_accepted, &size_OUT_buf_accepted);


  tcmanager_recent_error.kind = T_Runtime_Error_noerror_PRESENT;
}



void tcmanager_RI_PollTC_To_PID(asn1SccPID dest_pid, 
      asn1SccRxTC *OUT_accepted
);
void tcmanager_RI_PollTC(
      asn1SccRxTC *OUT_accepted
);
void tcmanager_RI_PollTC(
      asn1SccRxTC *OUT_accepted
)
{
   // When no destination is specified, send to everyone (multicast)
   tcmanager_RI_PollTC_To_PID(PID_env, OUT_accepted
);
}

void tcmanager_RI_PollTC_To_PID(asn1SccPID dest_pid, 
      asn1SccRxTC *OUT_accepted
)
{
   // Log MSC data on Linux when environment variable is set
   static int innerMsc = -1;
   if (-1 == innerMsc)
      innerMsc = (NULL != getenv("TASTE_INNER_MSC"))?1:0;
   if (1 == innerMsc) {
      long long msc_time = getTimeInMilliseconds();
      // Log message to Legacy (corresponding PI: PollTC)
      printf ("INNER_RI: tcmanager,legacy,polltc,polltc,%lld\n", msc_time);
      fflush(stdout);
   }

   size_t      size_OUT_buf_accepted = 0;

   // Send the message via the middleware API
   extern void vm_tcmanager_polltc
     (asn1SccPID,
      void *, size_t *);

   vm_tcmanager_polltc
     (dest_pid,
      (void *)OUT_accepted, &size_OUT_buf_accepted);


  tcmanager_recent_error.kind = T_Runtime_Error_noerror_PRESENT;
}



void tcmanager_RI_Reboot_To_PID(asn1SccPID dest_pid);
void tcmanager_RI_Reboot(void);
void tcmanager_RI_Reboot(void)
{
   // When no destination is specified, send to everyone (multicast)
   tcmanager_RI_Reboot_To_PID(PID_env);
}

void tcmanager_RI_Reboot_To_PID(asn1SccPID dest_pid)
{
   // Log MSC data on Linux when environment variable is set
   static int innerMsc = -1;
   if (-1 == innerMsc)
      innerMsc = (NULL != getenv("TASTE_INNER_MSC"))?1:0;
   if (1 == innerMsc) {
      long long msc_time = getTimeInMilliseconds();
      // Log message to Legacy (corresponding PI: Reboot)
      printf ("INNER_RI: tcmanager,legacy,reboot,reboot,%lld\n", msc_time);
      fflush(stdout);
   }


   // Send the message via the middleware API
   extern void vm_tcmanager_reboot(asn1SccPID);
   vm_tcmanager_reboot(dest_pid);

  tcmanager_recent_error.kind = T_Runtime_Error_noerror_PRESENT;
}



void tcmanager_RI_SBKGTC_To_PID(asn1SccPID dest_pid, 
      const asn1SccRawTC *IN_packet
);
void tcmanager_RI_SBKGTC(
      const asn1SccRawTC *IN_packet
);
void tcmanager_RI_SBKGTC(
      const asn1SccRawTC *IN_packet
)
{
   // When no destination is specified, send to everyone (multicast)
   tcmanager_RI_SBKGTC_To_PID(PID_env, IN_packet
);
}

void tcmanager_RI_SBKGTC_To_PID(asn1SccPID dest_pid, 
      const asn1SccRawTC *IN_packet
)
{
   // Log MSC data on Linux when environment variable is set
   static int innerMsc = -1;
   if (-1 == innerMsc)
      innerMsc = (NULL != getenv("TASTE_INNER_MSC"))?1:0;
   if (1 == innerMsc) {
      long long msc_time = getTimeInMilliseconds();
      // Log message to BKGTCExec (corresponding PI: SBKGTC)
      printf ("INNER_RI: tcmanager,bkgtcexec,sbkgtc,sbkgtc,%lld\n", msc_time);
      fflush(stdout);
   }


   // Send the message via the middleware API
   extern void vm_tcmanager_sbkgtc
     (asn1SccPID,
      void *, size_t);

   vm_tcmanager_sbkgtc
     (dest_pid,
      (void *)IN_packet, sizeof(asn1SccRawTC));


  tcmanager_recent_error.kind = T_Runtime_Error_noerror_PRESENT;
}



void tcmanager_RI_SHKFDIRTC_To_PID(asn1SccPID dest_pid, 
      const asn1SccRawTC *IN_packet
);
void tcmanager_RI_SHKFDIRTC(
      const asn1SccRawTC *IN_packet
);
void tcmanager_RI_SHKFDIRTC(
      const asn1SccRawTC *IN_packet
)
{
   // When no destination is specified, send to everyone (multicast)
   tcmanager_RI_SHKFDIRTC_To_PID(PID_env, IN_packet
);
}

void tcmanager_RI_SHKFDIRTC_To_PID(asn1SccPID dest_pid, 
      const asn1SccRawTC *IN_packet
)
{
   // Log MSC data on Linux when environment variable is set
   static int innerMsc = -1;
   if (-1 == innerMsc)
      innerMsc = (NULL != getenv("TASTE_INNER_MSC"))?1:0;
   if (1 == innerMsc) {
      long long msc_time = getTimeInMilliseconds();
      // Log message to HKFDIRMng (corresponding PI: SHKFDIRTC)
      printf ("INNER_RI: tcmanager,hkfdirmng,shkfdirtc,shkfdirtc,%lld\n", msc_time);
      fflush(stdout);
   }


   // Send the message via the middleware API
   extern void vm_tcmanager_shkfdirtc
     (asn1SccPID,
      void *, size_t);

   vm_tcmanager_shkfdirtc
     (dest_pid,
      (void *)IN_packet, sizeof(asn1SccRawTC));


  tcmanager_recent_error.kind = T_Runtime_Error_noerror_PRESENT;
}

// Get the PID of the sender function. The actual function is defined in _vm_if.c
// as the sender PID is received together with incoming PI calls
void tcmanager_RI_get_sender(asn1SccPID *sender_pid)
{
  extern void tcmanager_get_sender(asn1SccPID *sender_pid);
  tcmanager_get_sender(sender_pid);
}

void tcmanager_RI_get_last_error(asn1SccT_Runtime_Error* err)
{
    *err = tcmanager_recent_error;
}

void tcmanager_get_last_error(asn1SccT_Runtime_Error* err, const asn1SccPID* dest)
{
    tcmanager_RI_get_last_error(err);
}


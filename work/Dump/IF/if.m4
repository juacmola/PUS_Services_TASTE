divert(-1)
/*
*  This m4 file uses the following diverts:
*    1 for overall structure
*    5 for cast functions for GUI parameter subtypes
*    7 for num functions on Enum types
*    10 for signals
*    20 for functions
*/dnl
include(templates.m4)
divert(-1)
define(`m4_bkgtcexec_execbkgtc',`legacy_execbkgtc')dnl
define(`m4_bkgtcexec_ExecBKGTC_provider',`legacy')dnl
define(`m4_hkfdirmng_dohousekeeping',`legacy_dohousekeeping')dnl
define(`m4_hkfdirmng_DoHousekeeping_provider',`legacy')dnl
define(`m4_hkfdirmng_exechkfdirtc',`legacy_exechkfdirtc')dnl
define(`m4_hkfdirmng_ExecHKFDIRTC_provider',`legacy')dnl
define(`m4_hkfdirmng_sevaction',`tcmanager_sevaction')dnl
define(`m4_hkfdirmng_SEvAction_provider',`tcmanager')dnl
define(`m4_tcmanager_handletc',`legacy_handletc')dnl
define(`m4_tcmanager_HandleTC_provider',`legacy')dnl
define(`m4_tcmanager_init',`legacy_init')dnl
define(`m4_tcmanager_Init_provider',`legacy')dnl
define(`m4_tcmanager_newevaction',`legacy_newevaction')dnl
define(`m4_tcmanager_NewEvAction_provider',`legacy')dnl
define(`m4_tcmanager_newrxtc',`legacy_newrxtc')dnl
define(`m4_tcmanager_NewRxTC_provider',`legacy')dnl
define(`m4_tcmanager_polltc',`legacy_polltc')dnl
define(`m4_tcmanager_PollTC_provider',`legacy')dnl
define(`m4_tcmanager_reboot',`legacy_reboot')dnl
define(`m4_tcmanager_Reboot_provider',`legacy')dnl
define(`m4_tcmanager_sbkgtc',`bkgtcexec_sbkgtc')dnl
define(`m4_tcmanager_SBKGTC_provider',`bkgtcexec')dnl
define(`m4_tcmanager_shkfdirtc',`hkfdirmng_shkfdirtc')dnl
define(`m4_tcmanager_SHKFDIRTC_provider',`hkfdirmng')dnl
define(`m4_env_trigger',`hkfdirmng_trigger')dnl
define(`m4_env_trigger_provider',`hkfdirmng')dnl
define(`m4_env_poll',`tcmanager_poll')dnl
define(`m4_env_poll_provider',`tcmanager')dnl
divert(1)dnl
system taste;
/*
 *
 * Data View
 *
 */
include(dataview.if)

type math = abstract
    integer abs(integer);
    real abs(real);
    integer fix(real);
    real power(real, real);
    integer Shift_Left(integer, integer);
    integer Shift_Right(integer, integer);
    integer ceil(real);
    integer floor(real);
    real float(integer);
    integer round(real);
    real sin(real);
    real cos(real);
    integer trunc(real);
endabstract;

type enum_functions = abstract
undivert(7)
endabstract;


divert(20)
m4_sporadic_itf_handler(
    bkgtcexec,
    sbkgtc,
    RawTC,
     0,
     1)




include(bkgtcexec.if)

m4_sporadic_itf_handler(
    hkfdirmng,
    shkfdirtc,
    RawTC,
     0,
     1)

m4_cyclic_itf_handler(
    hkfdirmng,
    trigger,
     1000,
     1)






include(hkfdirmng.if)

m4_c_function(legacy,(DoHousekeeping,(),(),(), 0),

(ExecBKGTC,(packet),(RawTC),(PARAM_IN), 0),

(ExecHKFDIRTC,(packet),(RawTC),(PARAM_IN), 0),

(HandleTC,(route, packet),(FwdCommand, RawTC),(PARAM_OUT, PARAM_OUT), 0),

(Init,(),(),(), 0),

(NewEvAction,(accepted),(RxTC),(PARAM_OUT), 0),

(NewRxTC,(tc, accepted),(Telecommand, RxTC),(PARAM_IN, PARAM_OUT), 0),

(PollTC,(accepted),(RxTC),(PARAM_OUT), 0),

(Reboot,(),(),(), 0),

)

m4_sporadic_itf_handler(
    tcmanager,
    sevaction,
    ,
     0,
     10)

m4_cyclic_itf_handler(
    tcmanager,
    poll,
     100,
     1)











include(tcmanager.if)



divert(1)
type assign = abstract
undivert(5)
endabstract;

/*
 *
 * Interface View
 *
 */
signal set_timer(integer);
signal reset_timer();

undivert(10)

undivert(20)

endsystem;

priorityrules
undivert(30)
endpriorityrules;

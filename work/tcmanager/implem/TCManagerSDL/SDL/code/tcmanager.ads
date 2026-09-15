-- This file was generated automatically by OpenGEODE: DO NOT MODIFY IT !

with Interfaces,
     Interfaces.C.Strings,
     Ada.Characters.Handling;

use Interfaces,
    Interfaces.C.Strings,
    Ada.Characters.Handling;

with SCTRE_DATAVIEW;
use SCTRE_DATAVIEW;
with TASTE_BasicTypes;
use TASTE_BasicTypes;
with System_Dataview;
use System_Dataview;
with adaasn1rtl;
use adaasn1rtl;
with Tcmanager_Datamodel; use Tcmanager_Datamodel;

with Tcmanager_RI;
package Tcmanager with Elaborate_Body is
   
   self : constant asn1SccPID := asn1Scctcmanager;
   Default_Context: constant asn1SccTcmanager_Context :=
      (Init_Done => False,
       sender => asn1Sccenv,
       offspring => asn1Sccenv,
       others => <>);
   ctxt : aliased asn1SccTcmanager_Context := Default_Context;
   function To_T_Runtime_Error_Selection (Src : TASTE_BasicTypes.asn1SccT_Runtime_Error_Selection) return Tcmanager_Datamodel.asn1SccTcmanager_T_Runtime_Error_Selection is (Tcmanager_Datamodel.asn1SccTcmanager_T_Runtime_Error_Selection'Enum_Val (Src'Enum_Rep));
   function Get_State return Chars_Ptr is (Tcmanager_RI.To_C_Pointer (asn1SccTcmanager_States'Image (ctxt.State))) with Export, Convention => C, Link_Name => "tcmanager_state";
   procedure Startup with Export, Convention => C, Link_Name => "tcmanager_startup";
   --  Provided interface "SEvAction"
   procedure SEvAction;
   pragma Export(C, SEvAction, "tcmanager_PI_SEvAction");
   --  Provided interface "poll"
   procedure poll;
   pragma Export(C, poll, "tcmanager_PI_poll");
   --  Required interface "SBKGTC"
   procedure RI_0_SBKGTC(packet : in out asn1SccRawTC; Dest_PID : asn1SccPID := asn1SccEnv) renames Tcmanager_RI.SBKGTC;
   --  Required interface "SHKFDIRTC"
   procedure RI_0_SHKFDIRTC(packet : in out asn1SccRawTC; Dest_PID : asn1SccPID := asn1SccEnv) renames Tcmanager_RI.SHKFDIRTC;
   --  Synchronous Required Interface "HandleTC"
   procedure RI_0_HandleTC (Route : out asn1SccFwdCommand; Packet : out asn1SccRawTC; Dest_PID : asn1SccPID := asn1SccEnv) renames Tcmanager_RI.HandleTC;
   --  Synchronous Required Interface "Init"
   procedure RI_0_Init (Dest_PID : asn1SccPID := asn1SccEnv) renames Tcmanager_RI.Init;
   --  Synchronous Required Interface "NewEvAction"
   procedure RI_0_NewEvAction (Accepted : out asn1SccRxTC; Dest_PID : asn1SccPID := asn1SccEnv) renames Tcmanager_RI.NewEvAction;
   --  Synchronous Required Interface "NewRxTC"
   procedure RI_0_NewRxTC (Tc : in out asn1SccTelecommand; Accepted : out asn1SccRxTC; Dest_PID : asn1SccPID := asn1SccEnv) renames Tcmanager_RI.NewRxTC;
   --  Synchronous Required Interface "PollTC"
   procedure RI_0_PollTC (Accepted : out asn1SccRxTC; Dest_PID : asn1SccPID := asn1SccEnv) renames Tcmanager_RI.PollTC;
   --  Synchronous Required Interface "Reboot"
   procedure RI_0_Reboot (Dest_PID : asn1SccPID := asn1SccEnv) renames Tcmanager_RI.Reboot;
   --  Synchronous Required Interface "get_sender"
   procedure RI_0_get_sender (sender : out asn1SccPID; Dest_PID : asn1SccPID := asn1SccEnv) renames Tcmanager_RI.get_sender;
   --  Synchronous Required Interface "get_last_error"
   procedure RI_0_get_last_error (err : out asn1SccT_Runtime_Error; Dest_PID : asn1SccPID := asn1SccEnv) renames Tcmanager_RI.get_last_error;
   procedure Execute_Transition (Id : Integer);
   CS_Only : constant := 5;
   procedure Check_Queue (Res : out Asn1Boolean)
   with Import, Convention => C, Link_Name => "tcmanager_check_queue";
end Tcmanager;
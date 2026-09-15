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
with Hkfdirmng_Datamodel; use Hkfdirmng_Datamodel;

with Hkfdirmng_RI;
package Hkfdirmng with Elaborate_Body is
   
   self : constant asn1SccPID := asn1Scchkfdirmng;
   Default_Context: constant asn1SccHkfdirmng_Context :=
      (Init_Done => False,
       sender => asn1Sccenv,
       offspring => asn1Sccenv,
       others => <>);
   ctxt : aliased asn1SccHkfdirmng_Context := Default_Context;
   function To_T_Runtime_Error_Selection (Src : TASTE_BasicTypes.asn1SccT_Runtime_Error_Selection) return Hkfdirmng_Datamodel.asn1SccHkfdirmng_T_Runtime_Error_Selection is (Hkfdirmng_Datamodel.asn1SccHkfdirmng_T_Runtime_Error_Selection'Enum_Val (Src'Enum_Rep));
   function Get_State return Chars_Ptr is (Hkfdirmng_RI.To_C_Pointer (asn1SccHkfdirmng_States'Image (ctxt.State))) with Export, Convention => C, Link_Name => "hkfdirmng_state";
   procedure Startup with Export, Convention => C, Link_Name => "hkfdirmng_startup";
   --  Provided interface "SHKFDIRTC"
   procedure SHKFDIRTC(packet: in out asn1SccRawTC);
   pragma Export(C, SHKFDIRTC, "hkfdirmng_PI_SHKFDIRTC");
   --  Provided interface "trigger"
   procedure trigger;
   pragma Export(C, trigger, "hkfdirmng_PI_trigger");
   --  Paramless required interface "SEvAction"
   procedure RI_0_SEvAction(Dest_PID : asn1SccPID := asn1SccEnv) renames Hkfdirmng_RI.SEvAction;
   --  Synchronous Required Interface "DoHousekeeping"
   procedure RI_0_DoHousekeeping (Dest_PID : asn1SccPID := asn1SccEnv) renames Hkfdirmng_RI.DoHousekeeping;
   --  Synchronous Required Interface "ExecHKFDIRTC"
   procedure RI_0_ExecHKFDIRTC (Packet : in out asn1SccRawTC; Dest_PID : asn1SccPID := asn1SccEnv) renames Hkfdirmng_RI.ExecHKFDIRTC;
   --  Synchronous Required Interface "get_sender"
   procedure RI_0_get_sender (sender : out asn1SccPID; Dest_PID : asn1SccPID := asn1SccEnv) renames Hkfdirmng_RI.get_sender;
   --  Synchronous Required Interface "get_last_error"
   procedure RI_0_get_last_error (err : out asn1SccT_Runtime_Error; Dest_PID : asn1SccPID := asn1SccEnv) renames Hkfdirmng_RI.get_last_error;
   procedure Execute_Transition (Id : Integer);
   CS_Only : constant := 3;
end Hkfdirmng;
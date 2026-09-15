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
with Bkgtcexec_Datamodel; use Bkgtcexec_Datamodel;

with Bkgtcexec_RI;
package Bkgtcexec with Elaborate_Body is
   
   self : constant asn1SccPID := asn1Sccbkgtcexec;
   Default_Context: constant asn1SccBkgtcexec_Context :=
      (Init_Done => False,
       sender => asn1Sccenv,
       offspring => asn1Sccenv,
       others => <>);
   ctxt : aliased asn1SccBkgtcexec_Context := Default_Context;
   function To_T_Runtime_Error_Selection (Src : TASTE_BasicTypes.asn1SccT_Runtime_Error_Selection) return Bkgtcexec_Datamodel.asn1SccBkgtcexec_T_Runtime_Error_Selection is (Bkgtcexec_Datamodel.asn1SccBkgtcexec_T_Runtime_Error_Selection'Enum_Val (Src'Enum_Rep));
   function Get_State return Chars_Ptr is (Bkgtcexec_RI.To_C_Pointer (asn1SccBkgtcexec_States'Image (ctxt.State))) with Export, Convention => C, Link_Name => "bkgtcexec_state";
   procedure Startup with Export, Convention => C, Link_Name => "bkgtcexec_startup";
   --  Provided interface "SBKGTC"
   procedure SBKGTC(packet: in out asn1SccRawTC);
   pragma Export(C, SBKGTC, "bkgtcexec_PI_SBKGTC");
   --  Synchronous Required Interface "ExecBKGTC"
   procedure RI_0_ExecBKGTC (Packet : in out asn1SccRawTC; Dest_PID : asn1SccPID := asn1SccEnv) renames Bkgtcexec_RI.ExecBKGTC;
   --  Synchronous Required Interface "get_sender"
   procedure RI_0_get_sender (sender : out asn1SccPID; Dest_PID : asn1SccPID := asn1SccEnv) renames Bkgtcexec_RI.get_sender;
   --  Synchronous Required Interface "get_last_error"
   procedure RI_0_get_last_error (err : out asn1SccT_Runtime_Error; Dest_PID : asn1SccPID := asn1SccEnv) renames Bkgtcexec_RI.get_last_error;
   procedure Execute_Transition (Id : Integer);
   CS_Only : constant := 2;
end Bkgtcexec;
-- This file was generated automatically by OpenGEODE: DO NOT MODIFY IT !

with Text_IO; use Text_IO;


package body Hkfdirmng is
   procedure p_0_ExecTC;
   procedure p_0_evTCEventAction;
   procedure p_0_ExecTC is
      begin
         --  ExecHKFDIRTC(packet) (16,17)
         RI_0_ExecHKFDIRTC(ctxt.packet);
         --  RETURN  (None,None) at 400, 204
         return;
      end p_0_ExecTC;
      

   procedure p_0_evTCEventAction is
      begin
         --  SEvAction (26,19)
         RI_0_SEvAction;
         --  RETURN  (None,None) at 473, 232
         return;
      end p_0_evTCEventAction;
      

   procedure SHKFDIRTC(packet: in out asn1SccRawTC) is
      begin
         case ctxt.state is
            when asn1Sccready =>
               ctxt.packet := packet;
               Execute_Transition (1);
            when others =>
               Execute_Transition (CS_Only);
         end case;
      end SHKFDIRTC;
      

   procedure trigger is
      begin
         case ctxt.state is
            when asn1Sccready =>
               Execute_Transition (2);
            when others =>
               Execute_Transition (CS_Only);
         end case;
      end trigger;
      

   procedure Execute_Transition (Id : Integer) is
      trId : Integer := Id;
      begin
         if not ctxt.Init_Done and trId /= 0 then
            return;
         end if;
         while (trId /= -1) loop
            case trId is
               when 0 =>
                  --  writeln("[HK_FDIRMng] Startup") (33,13)
                  Put ("[HK_FDIRMng] Startup");
                  New_Line;
                  --  NEXT_STATE Ready (35,18) at 74, 118
                  trId := -1;
                  ctxt.State := asn1SccReady;
                  goto Continuous_Signals;
               when 1 =>
                  --  get_sender(sender) (1,5)
                  RI_0_get_sender(ctxt.sender);
                  --  ExecTC (42,17)
                  p_0_ExecTC;
                  --  NEXT_STATE Ready (44,22) at 550, 165
                  trId := -1;
                  ctxt.State := asn1SccReady;
                  goto Continuous_Signals;
               when 2 =>
                  --  get_sender(sender) (1,5)
                  RI_0_get_sender(ctxt.sender);
                  --  DoHousekeeping (48,17)
                  RI_0_DoHousekeeping;
                  --  evTCEventAction (50,17)
                  p_0_evTCEventAction;
                  --  NEXT_STATE Ready (52,22) at 298, 275
                  trId := -1;
                  ctxt.State := asn1SccReady;
                  goto Continuous_Signals;
               when CS_Only =>
                  trId := -1;
                  goto Continuous_Signals;
               when others =>
                  null;
            end case;
            <<Continuous_Signals>>
            <<Next_Transition>>
         end loop;
      end Execute_Transition;
      

   procedure Startup is
      begin
         Execute_Transition (0);
         ctxt.Init_Done := True;
      end Startup;
end Hkfdirmng;
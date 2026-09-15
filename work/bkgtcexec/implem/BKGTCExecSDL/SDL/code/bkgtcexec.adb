-- This file was generated automatically by OpenGEODE: DO NOT MODIFY IT !

with Text_IO; use Text_IO;


package body Bkgtcexec is
   procedure p_0_ExecTC;
   procedure p_0_ExecTC is
      begin
         --  ExecBKGTC(packet) (14,17)
         RI_0_ExecBKGTC(ctxt.packet);
         --  RETURN  (None,None) at 343, 162
         return;
      end p_0_ExecTC;
      

   procedure SBKGTC(packet: in out asn1SccRawTC) is
      begin
         case ctxt.state is
            when asn1Sccready =>
               ctxt.packet := packet;
               Execute_Transition (1);
            when others =>
               Execute_Transition (CS_Only);
         end case;
      end SBKGTC;
      

   procedure Execute_Transition (Id : Integer) is
      trId : Integer := Id;
      begin
         if not ctxt.Init_Done and trId /= 0 then
            return;
         end if;
         while (trId /= -1) loop
            case trId is
               when 0 =>
                  --  writeln("[BKGT] Startup") (21,13)
                  Put ("[BKGT] Startup");
                  New_Line;
                  --  NEXT_STATE Ready (23,18) at 182, 105
                  trId := -1;
                  ctxt.State := asn1SccReady;
                  goto Continuous_Signals;
               when 1 =>
                  --  get_sender(sender) (1,5)
                  RI_0_get_sender(ctxt.sender);
                  --  ExecTC (30,17)
                  p_0_ExecTC;
                  --  NEXT_STATE Ready (32,22) at 459, 170
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
end Bkgtcexec;
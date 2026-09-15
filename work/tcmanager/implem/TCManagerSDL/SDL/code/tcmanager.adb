-- This file was generated automatically by OpenGEODE: DO NOT MODIFY IT !

with Text_IO; use Text_IO;


package body Tcmanager is
   procedure p_0_doHandleTC;
   procedure p_0_doReboot;
   procedure p_0_doNewEvAction;
   procedure p_0_doNewRxTC;
   procedure p_0_doInit;
   procedure p_0_doHandleTC is
      begin
         --  HandleTC(fwdComm, packet) (18,17)
         RI_0_HandleTC(ctxt.fwdComm, ctxt.packet);
         --  RETURN  (None,None) at 306, 231
         return;
      end p_0_doHandleTC;
      

   procedure p_0_doReboot is
      begin
         --  Reboot (28,17)
         RI_0_Reboot;
         --  RETURN  (None,None) at 235, 177
         return;
      end p_0_doReboot;
      

   procedure p_0_doNewEvAction is
      begin
         --  NewEvAction(acceptance) (38,17)
         RI_0_NewEvAction(ctxt.acceptance);
         --  RETURN  (None,None) at 250, 185
         return;
      end p_0_doNewEvAction;
      

   procedure p_0_doNewRxTC is
      begin
         --  NewRxTC(tc, acceptance) (48,17)
         RI_0_NewRxTC(ctxt.tc, ctxt.acceptance);
         --  RETURN  (None,None) at 162, 150
         return;
      end p_0_doNewRxTC;
      

   procedure p_0_doInit is
      begin
         --  Init (58,17)
         RI_0_Init;
         --  RETURN  (None,None) at 199, 163
         return;
      end p_0_doInit;
      

   procedure SEvAction is
      begin
         case ctxt.state is
            when asn1Sccready =>
               Execute_Transition (2);
            when others =>
               Execute_Transition (CS_Only);
         end case;
      end SEvAction;
      

   procedure poll is
      begin
         case ctxt.state is
            when asn1Sccready =>
               Execute_Transition (1);
            when others =>
               Execute_Transition (CS_Only);
         end case;
      end poll;
      

   procedure Execute_Transition (Id : Integer) is
      trId : Integer := Id;
      Message_Pending : Asn1Boolean := True;
      begin
         if not ctxt.Init_Done and trId /= 0 then
            return;
         end if;
         while (trId /= -1) loop
            case trId is
               when 0 =>
                  --  writeln("[TCManager] starts") (65,13)
                  Put ("[TCManager] starts");
                  New_Line;
                  --  doInit (67,13)
                  p_0_doInit;
                  --  NEXT_STATE Ready (69,18) at 63, 181
                  trId := -1;
                  ctxt.State := asn1SccReady;
                  goto Continuous_Signals;
               when 1 =>
                  --  get_sender(sender) (1,5)
                  RI_0_get_sender(ctxt.sender);
                  --  PollTC(acceptance) (76,17)
                  RI_0_PollTC(ctxt.acceptance);
                  --  DECISION acceptance (-1,-1)
                  --  ANSWER accepted (80,17)
                  if (ctxt.acceptance) = asn1Sccaccepted then
                     --  NEXT_STATE ValidTC (82,30) at 367, 286
                     trId := -1;
                     ctxt.State := asn1SccValidTC;
                     goto Continuous_Signals;
                     --  ANSWER not_accepted (84,17)
                  elsif (ctxt.acceptance) = asn1Sccnot_accepted then
                     --  NEXT_STATE Ready (86,30) at 458, 286
                     trId := -1;
                     ctxt.State := asn1SccReady;
                     goto Continuous_Signals;
                  end if;
               when 2 =>
                  --  get_sender(sender) (1,5)
                  RI_0_get_sender(ctxt.sender);
                  --  donewevaction (91,17)
                  p_0_doNewEvAction;
                  --  NEXT_STATE ValidTC (93,22) at 577, 188
                  trId := -1;
                  ctxt.State := asn1SccValidTC;
                  goto Continuous_Signals;
               when 3 =>
                  --  doHandletc (101,17)
                  p_0_doHandleTC;
                  --  DECISION fwdComm (-1,-1)
                  --  COMMENT HandleTC (105,12)
                  --  ANSWER exec_prio_tc (107,17)
                  if (ctxt.fwdComm) = asn1Sccexec_prio_tc then
                     --  NEXT_STATE Ready (109,30) at 802, 391
                     trId := -1;
                     ctxt.State := asn1SccReady;
                     goto Continuous_Signals;
                     --  ANSWER to_reboot (111,17)
                  elsif (ctxt.fwdComm) = asn1Sccto_reboot then
                     --  NEXT_STATE Reboot (113,30) at 667, 391
                     trId := -1;
                     ctxt.State := asn1SccReboot;
                     goto Continuous_Signals;
                     --  ANSWER fwdhk_fdir_tc (115,17)
                  elsif (ctxt.fwdComm) = asn1Sccfwdhk_fdir_tc then
                     --  SHKFDIRTC(packet) (117,27)
                     RI_0_SHKFDIRTC(ctxt.packet);
                     --  ANSWER fwdbkgtc (119,17)
                  elsif (ctxt.fwdComm) = asn1Sccfwdbkgtc then
                     --  SBKGTC(packet) (121,27)
                     RI_0_SBKGTC(ctxt.packet);
                  end if;
                  --  NEXT_STATE Ready (124,22) at 876, 445
                  trId := -1;
                  ctxt.State := asn1SccReady;
                  goto Continuous_Signals;
               when 4 =>
                  --  doreboot (132,17)
                  p_0_doReboot;
               when CS_Only =>
                  trId := -1;
                  goto Continuous_Signals;
               when others =>
                  null;
            end case;
            <<Continuous_Signals>>
            --  Process continuous signals
            if ctxt.Init_Done then
               Check_Queue (Message_Pending);
            end if;
            if Message_Pending or trId /= -1 then
               goto Next_Transition;
            end if;
            if ctxt.State = asn1Sccreboot then
               --  Priority: 1
               --  DECISION true (-1,-1)
               --  ANSWER true (None,None)
               if (true) then
                  trId := 4;
               end if;
            end if;
            if ctxt.State = asn1Sccvalidtc then
               --  Priority: 1
               --  DECISION true (-1,-1)
               --  ANSWER true (None,None)
               if (true) then
                  trId := 3;
               end if;
            end if;
            <<Next_Transition>>
         end loop;
      end Execute_Transition;
      

   procedure Startup is
      begin
         Execute_Transition (0);
         ctxt.Init_Done := True;
      end Startup;
end Tcmanager;
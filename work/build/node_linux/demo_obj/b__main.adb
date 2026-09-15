pragma Warnings (Off);
pragma Ada_95;
pragma Source_File_Name (ada_main, Spec_File_Name => "b__main.ads");
pragma Source_File_Name (ada_main, Body_File_Name => "b__main.adb");
pragma Suppress (Overflow_Check);
with Ada.Exceptions;

package body ada_main is

   E105 : Short_Integer; pragma Import (Ada, E105, "system__os_lib_E");
   E038 : Short_Integer; pragma Import (Ada, E038, "ada__exceptions_E");
   E042 : Short_Integer; pragma Import (Ada, E042, "system__soft_links_E");
   E054 : Short_Integer; pragma Import (Ada, E054, "system__exception_table_E");
   E077 : Short_Integer; pragma Import (Ada, E077, "ada__containers_E");
   E100 : Short_Integer; pragma Import (Ada, E100, "ada__io_exceptions_E");
   E061 : Short_Integer; pragma Import (Ada, E061, "ada__numerics_E");
   E089 : Short_Integer; pragma Import (Ada, E089, "ada__strings_E");
   E091 : Short_Integer; pragma Import (Ada, E091, "ada__strings__maps_E");
   E092 : Short_Integer; pragma Import (Ada, E092, "ada__strings__maps__constants_E");
   E081 : Short_Integer; pragma Import (Ada, E081, "interfaces__c_E");
   E055 : Short_Integer; pragma Import (Ada, E055, "system__exceptions_E");
   E114 : Short_Integer; pragma Import (Ada, E114, "system__object_reader_E");
   E086 : Short_Integer; pragma Import (Ada, E086, "system__dwarf_lines_E");
   E050 : Short_Integer; pragma Import (Ada, E050, "system__soft_links__initialize_E");
   E076 : Short_Integer; pragma Import (Ada, E076, "system__traceback__symbolic_E");
   E060 : Short_Integer; pragma Import (Ada, E060, "system__img_int_E");
   E095 : Short_Integer; pragma Import (Ada, E095, "system__img_uns_E");
   E133 : Short_Integer; pragma Import (Ada, E133, "ada__strings__utf_encoding_E");
   E141 : Short_Integer; pragma Import (Ada, E141, "ada__tags_E");
   E131 : Short_Integer; pragma Import (Ada, E131, "ada__strings__text_buffers_E");
   E164 : Short_Integer; pragma Import (Ada, E164, "interfaces__c__strings_E");
   E150 : Short_Integer; pragma Import (Ada, E150, "ada__streams_E");
   E162 : Short_Integer; pragma Import (Ada, E162, "system__file_control_block_E");
   E161 : Short_Integer; pragma Import (Ada, E161, "system__finalization_root_E");
   E159 : Short_Integer; pragma Import (Ada, E159, "ada__finalization_E");
   E158 : Short_Integer; pragma Import (Ada, E158, "system__file_io_E");
   E148 : Short_Integer; pragma Import (Ada, E148, "ada__text_io_E");
   E002 : Short_Integer; pragma Import (Ada, E002, "adaasn1rtl_E");
   E017 : Short_Integer; pragma Import (Ada, E017, "sctre_dataview_E");
   E019 : Short_Integer; pragma Import (Ada, E019, "system_dataview_E");
   E006 : Short_Integer; pragma Import (Ada, E006, "bkgtcexec_datamodel_E");
   E013 : Short_Integer; pragma Import (Ada, E013, "hkfdirmng_datamodel_E");
   E021 : Short_Integer; pragma Import (Ada, E021, "taste_basictypes_E");
   E008 : Short_Integer; pragma Import (Ada, E008, "bkgtcexec_ri_E");
   E015 : Short_Integer; pragma Import (Ada, E015, "hkfdirmng_ri_E");
   E025 : Short_Integer; pragma Import (Ada, E025, "tcmanager_datamodel_E");
   E027 : Short_Integer; pragma Import (Ada, E027, "tcmanager_ri_E");

   Sec_Default_Sized_Stacks : array (1 .. 1) of aliased System.Secondary_Stack.SS_Stack (System.Parameters.Runtime_Default_Sec_Stack_Size);

   Local_Priority_Specific_Dispatching : constant String := "";
   Local_Interrupt_States : constant String := "";

   Is_Elaborated : Boolean := False;

   procedure finalize_library is
   begin
      E148 := E148 - 1;
      declare
         procedure F1;
         pragma Import (Ada, F1, "ada__text_io__finalize_spec");
      begin
         if E148 = 0 then
            F1;
         end if;
      end;
      declare
         procedure F2;
         pragma Import (Ada, F2, "system__file_io__finalize_body");
      begin
         E158 := E158 - 1;
         if E158 = 0 then
            F2;
         end if;
      end;
      declare
         procedure Reraise_Library_Exception_If_Any;
            pragma Import (Ada, Reraise_Library_Exception_If_Any, "__gnat_reraise_library_exception_if_any");
      begin
         Reraise_Library_Exception_If_Any;
      end;
   end finalize_library;

   procedure adafinal is
      procedure s_stalib_adafinal;
      pragma Import (Ada, s_stalib_adafinal, "system__standard_library__adafinal");

      procedure Runtime_Finalize;
      pragma Import (C, Runtime_Finalize, "__gnat_runtime_finalize");

   begin
      if not Is_Elaborated then
         return;
      end if;
      Is_Elaborated := False;
      Runtime_Finalize;
      s_stalib_adafinal;
   end adafinal;

   type No_Param_Proc is access procedure;
   pragma Favor_Top_Level (No_Param_Proc);

   procedure adainit is
      Main_Priority : Integer;
      pragma Import (C, Main_Priority, "__gl_main_priority");
      Time_Slice_Value : Integer;
      pragma Import (C, Time_Slice_Value, "__gl_time_slice_val");
      WC_Encoding : Character;
      pragma Import (C, WC_Encoding, "__gl_wc_encoding");
      Locking_Policy : Character;
      pragma Import (C, Locking_Policy, "__gl_locking_policy");
      Queuing_Policy : Character;
      pragma Import (C, Queuing_Policy, "__gl_queuing_policy");
      Task_Dispatching_Policy : Character;
      pragma Import (C, Task_Dispatching_Policy, "__gl_task_dispatching_policy");
      Priority_Specific_Dispatching : System.Address;
      pragma Import (C, Priority_Specific_Dispatching, "__gl_priority_specific_dispatching");
      Num_Specific_Dispatching : Integer;
      pragma Import (C, Num_Specific_Dispatching, "__gl_num_specific_dispatching");
      Main_CPU : Integer;
      pragma Import (C, Main_CPU, "__gl_main_cpu");
      Interrupt_States : System.Address;
      pragma Import (C, Interrupt_States, "__gl_interrupt_states");
      Num_Interrupt_States : Integer;
      pragma Import (C, Num_Interrupt_States, "__gl_num_interrupt_states");
      Unreserve_All_Interrupts : Integer;
      pragma Import (C, Unreserve_All_Interrupts, "__gl_unreserve_all_interrupts");
      Detect_Blocking : Integer;
      pragma Import (C, Detect_Blocking, "__gl_detect_blocking");
      Default_Stack_Size : Integer;
      pragma Import (C, Default_Stack_Size, "__gl_default_stack_size");
      Default_Secondary_Stack_Size : System.Parameters.Size_Type;
      pragma Import (C, Default_Secondary_Stack_Size, "__gnat_default_ss_size");
      Bind_Env_Addr : System.Address;
      pragma Import (C, Bind_Env_Addr, "__gl_bind_env_addr");

      procedure Runtime_Initialize (Install_Handler : Integer);
      pragma Import (C, Runtime_Initialize, "__gnat_runtime_initialize");

      Finalize_Library_Objects : No_Param_Proc;
      pragma Import (C, Finalize_Library_Objects, "__gnat_finalize_library_objects");
      Binder_Sec_Stacks_Count : Natural;
      pragma Import (Ada, Binder_Sec_Stacks_Count, "__gnat_binder_ss_count");
      Default_Sized_SS_Pool : System.Address;
      pragma Import (Ada, Default_Sized_SS_Pool, "__gnat_default_ss_pool");

   begin
      if Is_Elaborated then
         return;
      end if;
      Is_Elaborated := True;
      Main_Priority := -1;
      Time_Slice_Value := -1;
      WC_Encoding := 'b';
      Locking_Policy := ' ';
      Queuing_Policy := ' ';
      Task_Dispatching_Policy := ' ';
      Priority_Specific_Dispatching :=
        Local_Priority_Specific_Dispatching'Address;
      Num_Specific_Dispatching := 0;
      Main_CPU := -1;
      Interrupt_States := Local_Interrupt_States'Address;
      Num_Interrupt_States := 0;
      Unreserve_All_Interrupts := 0;
      Detect_Blocking := 0;
      Default_Stack_Size := -1;

      ada_main'Elab_Body;
      Default_Secondary_Stack_Size := System.Parameters.Runtime_Default_Sec_Stack_Size;
      Binder_Sec_Stacks_Count := 1;
      Default_Sized_SS_Pool := Sec_Default_Sized_Stacks'Address;

      Runtime_Initialize (1);

      Finalize_Library_Objects := finalize_library'access;

      if E038 = 0 then
         Ada.Exceptions'Elab_Spec;
      end if;
      if E042 = 0 then
         System.Soft_Links'Elab_Spec;
      end if;
      if E054 = 0 then
         System.Exception_Table'Elab_Body;
      end if;
      E054 := E054 + 1;
      if E077 = 0 then
         Ada.Containers'Elab_Spec;
      end if;
      E077 := E077 + 1;
      if E100 = 0 then
         Ada.Io_Exceptions'Elab_Spec;
      end if;
      E100 := E100 + 1;
      if E061 = 0 then
         Ada.Numerics'Elab_Spec;
      end if;
      E061 := E061 + 1;
      if E089 = 0 then
         Ada.Strings'Elab_Spec;
      end if;
      E089 := E089 + 1;
      if E091 = 0 then
         Ada.Strings.Maps'Elab_Spec;
      end if;
      E091 := E091 + 1;
      if E092 = 0 then
         Ada.Strings.Maps.Constants'Elab_Spec;
      end if;
      E092 := E092 + 1;
      if E081 = 0 then
         Interfaces.C'Elab_Spec;
      end if;
      E081 := E081 + 1;
      if E055 = 0 then
         System.Exceptions'Elab_Spec;
      end if;
      E055 := E055 + 1;
      if E114 = 0 then
         System.Object_Reader'Elab_Spec;
      end if;
      E114 := E114 + 1;
      if E086 = 0 then
         System.Dwarf_Lines'Elab_Spec;
      end if;
      if E105 = 0 then
         System.Os_Lib'Elab_Body;
      end if;
      E105 := E105 + 1;
      if E050 = 0 then
         System.Soft_Links.Initialize'Elab_Body;
      end if;
      E050 := E050 + 1;
      E042 := E042 + 1;
      if E076 = 0 then
         System.Traceback.Symbolic'Elab_Body;
      end if;
      E076 := E076 + 1;
      if E060 = 0 then
         System.Img_Int'Elab_Spec;
      end if;
      E060 := E060 + 1;
      E038 := E038 + 1;
      if E095 = 0 then
         System.Img_Uns'Elab_Spec;
      end if;
      E095 := E095 + 1;
      E086 := E086 + 1;
      if E133 = 0 then
         Ada.Strings.Utf_Encoding'Elab_Spec;
      end if;
      E133 := E133 + 1;
      if E141 = 0 then
         Ada.Tags'Elab_Spec;
      end if;
      if E141 = 0 then
         Ada.Tags'Elab_Body;
      end if;
      E141 := E141 + 1;
      if E131 = 0 then
         Ada.Strings.Text_Buffers'Elab_Spec;
      end if;
      E131 := E131 + 1;
      if E164 = 0 then
         Interfaces.C.Strings'Elab_Spec;
      end if;
      E164 := E164 + 1;
      if E150 = 0 then
         Ada.Streams'Elab_Spec;
      end if;
      E150 := E150 + 1;
      if E162 = 0 then
         System.File_Control_Block'Elab_Spec;
      end if;
      E162 := E162 + 1;
      if E161 = 0 then
         System.Finalization_Root'Elab_Spec;
      end if;
      E161 := E161 + 1;
      if E159 = 0 then
         Ada.Finalization'Elab_Spec;
      end if;
      E159 := E159 + 1;
      if E158 = 0 then
         System.File_Io'Elab_Body;
      end if;
      E158 := E158 + 1;
      if E148 = 0 then
         Ada.Text_Io'Elab_Spec;
      end if;
      if E148 = 0 then
         Ada.Text_Io'Elab_Body;
      end if;
      E148 := E148 + 1;
      E002 := E002 + 1;
      E017 := E017 + 1;
      E019 := E019 + 1;
      E006 := E006 + 1;
      E013 := E013 + 1;
      E021 := E021 + 1;
      E008 := E008 + 1;
      E015 := E015 + 1;
      E025 := E025 + 1;
      E027 := E027 + 1;
   end adainit;

--  BEGIN Object file/option list
   --   /home/jorge/sctre/work/build/node_linux/demo_obj/board_config.o
   --   /home/jorge/sctre/work/build/node_linux/demo_obj/adaasn1rtl.o
   --   /home/jorge/sctre/work/build/node_linux/demo_obj/sctre_dataview.o
   --   /home/jorge/sctre/work/build/node_linux/demo_obj/system_dataview.o
   --   /home/jorge/sctre/work/build/node_linux/demo_obj/bkgtcexec_datamodel.o
   --   /home/jorge/sctre/work/build/node_linux/demo_obj/hkfdirmng_datamodel.o
   --   /home/jorge/sctre/work/build/node_linux/demo_obj/taste_basictypes.o
   --   /home/jorge/sctre/work/build/node_linux/demo_obj/bkgtcexec_ri.o
   --   /home/jorge/sctre/work/build/node_linux/demo_obj/bkgtcexec.o
   --   /home/jorge/sctre/work/build/node_linux/demo_obj/hkfdirmng_ri.o
   --   /home/jorge/sctre/work/build/node_linux/demo_obj/hkfdirmng.o
   --   /home/jorge/sctre/work/build/node_linux/demo_obj/tcmanager_datamodel.o
   --   /home/jorge/sctre/work/build/node_linux/demo_obj/tcmanager_ri.o
   --   /home/jorge/sctre/work/build/node_linux/demo_obj/tcmanager.o
   --   -L/home/jorge/sctre/work/build/node_linux/demo_obj/
   --   -L/home/jorge/sctre/work/build/node_linux/demo_obj/
   --   -L/usr/lib/gcc/x86_64-linux-gnu/13/adalib/
   --   -shared
   --   -lgnat-13
   --   -ldl
--  END Object file/option list   

end ada_main;

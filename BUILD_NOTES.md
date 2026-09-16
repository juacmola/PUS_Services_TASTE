# TASTE Linux build

Run `make` from this directory. The configured deployment is `x86_generic_linux`,
not LEON3. The executable is `work/binaries/demo`; `make run` starts the TASTE
application and its GUI. No manual export from `comando.txt` is needed.

`legacy.mk` supplies the PUS sources and include directories. It intentionally
excludes the standalone EDROOM application tasks, RTEMS OS implementation, and
LEON interrupt-controller sources. TASTE owns the Linux task dispatch. The
emulated SC channel already ignores its IRQ argument, so Linux startup supplies
`nullptr`; the existing hardware startup sequence remains under the other
compile-time branch. This is a Linux integration, not a full RTEMS emulator or
a verified LEON3 cross-build. The mutex/time adapter provides recursive mutual
exclusion and monotonic deadlines, not RTEMS priority scheduling guarantees.

Other corrections cover stale includes, conflicting basic-type header guards,
fixed-width integer definitions, missing C linkage, a monitor enum conversion,
and reversed verification-stage/error-code arguments. Serialization now uses
the compiler's actual byte order while retaining big-endian PUS wire bytes.
The SDL state machines now pass typed receive, acceptance, routing and packet values.

Validation completed:

- Plain `make` and a forced recompilation of all partition sources linked.
- A five-second startup smoke test completed initialization of all five TASTE
  functions and emitted `GSS Rx TM [5,1]`; the test then stopped the process.
- `python3 tests/run_legacy_tests.py` passed with AddressSanitizer and UBSan.
  It checks known wire bytes, integer types, recursive/exclusive locking, and
  monotonic deadlines.

Telecommand bridge (legacy.cc review):

- `NewRxTC(tc, accepted)` consumes the GUI's `Telecommand` argument. It constructs
  a PUS packet with the mission APID/source ID, a 14-bit sequence counter, version
  2, all acknowledgement flags and a computed CRC, then runs acceptance. The
  GUI type still supplies exactly three application-data bytes; it does not
  represent an arbitrary incoming wire packet or a hardware IRQ descriptor.
- `NewEvAction(accepted)` treats SEvAction as notification and safely extracts
  one pending service-19 action. Empty queues/allocation failure leave no command
  to execute. HKFDIRMng sends a notification on its existing periodic trigger.
- `HandleTC(route, packet)` executes priority/reboot commands locally or returns
  a full `RawTC` packet and forwarding destination. FFwdHK_FDIRTC and FFwdBKGTC
  prepare the returned bytes. TCManager owns the existing required interfaces:
  SDL `output SHKFDIRTC(packet)` / `output SBKGTC(packet)` performs the asynchronous
  send. There is no EDROOM `Msg`, port or pool in the TASTE Legacy function.
- HKFDIRMng/BKGTCExec receive their own packet values and call the new protected
  Legacy `ExecHKFDIRTC` / `ExecBKGTC` interfaces. Each call rebuilds a local handler;
  no pointer into VCurrentTC crosses a TASTE queue. Protected Legacy calls also
  serialize access to the shared PUS services. The selected SDL implementations
  and generated glue were updated; alternate, unfinished C implementations were
  not completed as part of this change.
- Packet lengths are checked before the legacy parser accesses the CRC. Pool
  exhaustion, stale/repeated HandleTC calls and overwriting an accepted command
  are guarded. Releasing a TC now clears its pointer, preventing a second release
  from freeing storage reassigned to another command. Service-3 executors now
  include their C-linkage declarations. Service-19 extraction now checks the
  severity-2 queue in its corresponding branch.

Validation for the bridge:

- `make` regenerates the model/glue and links the Linux application.
- `python3 tests/run_legacy_routing_tests.py` builds the actual PUS and bridge
  sources with AddressSanitizer/UBSan. It checks acceptance/rejection, HK/BKG
  routing, payload preservation after another command arrives, priority execution,
  empty/event queues, severity-2 extraction, malformed lengths, allocation
  failure, complete pool recovery and double-release/reused-buffer handling.
- `python3 tests/run_taste_routing_smoke.py` starts the built application and sends
  commands via the generated GUI message-queue API. It verifies HK completion,
  delivery to BKG execution, priority execution and rejection through telemetry.
  Run it with no other instance of this application's GUI/demo using the queue.
- `python3 tests/run_legacy_tests.py` continues to pass.

Service 20 TC subtypes 1 and 3 are dispatched to their existing executors.
The service-20 smoke path checks the parameter-report TM and completion TM.
`CDTCHandler::GetExecCtrl` does not currently classify any command as reboot,
and its reboot executor is also a stub. No
hardware/LEON3 execution was performed. The existing queue capacities and
scheduling policy were not changed or stress-tested.

Existing warnings remain in generated Ada/GUI code and parts of the PUS library,
including potentially uninitialized error results and a switch fallthrough.
They were not suppressed. No hardware execution was performed; the Linux
end-to-end command checks are described above.

Original versions of edited files are under `build-fix-backup/` with matching
relative paths. New files are `legacy.mk`, this document, `tests/`, and
`work/asw_pus_rtems_5_0_leon3/taste_linux/legacy_primitives.cc`.

## emu_gss input (Linux TASTE)

Run `make run-gss` to build and run without opening the IRQ GUI. `make run`
still opens the GUI; both inputs can coexist. The default schedule sends a
TC[17,1] connection test at OBT_AFTER_POWER_ON + 2. Edit
`work/asw_pus_rtems_5_0_leon3/taste_linux/gss_schedule.cc` to add existing
`EmuGSS_TCProgram...` builders. Keep scheduled objects alive until consumed
(the example uses a function-local static). No new ASN.1 types are needed.

The maintained XML architecture now adds a 100 ms cyclic `TCManager.poll`
interface and a protected `Legacy.PollTC(accepted)` call. The latter advances
emulated seconds against monotonic time, runs due programs, and receives one
queued packet per dispatch. `BuildTC(tc_mem_descriptor_t&)` supplies complete
wire bytes; Legacy validates the length and copies them into pool storage
before acceptance. TCManager then uses its existing HandleTC/RawTC routing.
The GUI's three-byte Telecommand conversion remains a separate input path.

Linux delivery no longer signals the unused EDROOM IRQ18 from emu_gss;
the hardware branch retains that notification. Full receive queues defer due
programs until space becomes available; pool exhaustion retains the head
packet for retry. The ring tail calculation now wraps the entire index sum.
Emulator headers now identify a TC, PUS version 2 and the mission source ID.
The receive rate is at most ten packets per second; this does not guarantee
loss-free downstream delivery under arbitrary load with the existing small
executor queues. The onboard clock here serves the emulation; this change
does not implement the other standalone EDROOM periodic application tasks.

Validation: `make`, `python3 tests/run_legacy_routing_tests.py` (ASan/UBSan,
including 205 scheduled commands across queue-full and wraparound cases),
`python3 tests/run_legacy_tests.py`, `python3 tests/run_taste_gss_smoke.py`,
and `python3 tests/run_taste_routing_smoke.py` passed. The headless smoke
observes TC[17,1], acceptance TM[1,1], response TM[17,2] and completion TM[1,7].
Run application smoke tests sequentially without another demo instance.
Hardware/RTEMS execution remains untested.

## Periodic housekeeping in the current architecture

`HKFDIRMng.trigger` now has a 1000 ms period, a 1000 ms dispatch offset and
16 KiB stack. Its SDL handler calls the new protected `Legacy.DoHousekeeping`
interface, then sends the existing SEvAction notification to TCManager.
Previously the trigger only sent SEvAction every ten seconds, so it never
called `pus_service3_do_HK()` and no periodic TM[3,25] reports were generated.

The Legacy callback checks startup has completed, samples the ADC parameters
with `pus_services_update_params()`, and calls `pus_service3_do_HK()` once per
trigger. Generated TASTE glue holds the same Legacy mutex used by the TC
executors, serializing sampling/reporting and SID configuration changes.
Housekeeping intervals are measured in one-second trigger invocations. Missed
or delayed dispatches are not replayed using historical samples.

TM[3,25] follows the existing PUS telemetry path to the emulated SC channel
and emu_gss, which prints the SID and parameter values. TCManager receives
event-action notifications, not housekeeping telemetry. This change does not
add periodic FDIR monitoring or change the ASN.1 model.

The current model has no IRQ GUI. Use `make run-gss` (or build/run in TASTE)
with `EMU_TC_PROGRAMMING_ST03` selected in `taste_linux/gss_schedule_config.h`.
Change the define in this shared header to select another service test.
Only ST03 displays TM[3,25] on the terminal; the other scenarios hide these
reports while housekeeping generation and telemetry delivery continue.
This selects the existing emu_tc_programming_st03.cc file; it supersedes the
original service-17 example described above. Initial SID 0 reports every two
seconds (PIDs 0..4); SID 10 every four seconds (PIDs 5..7). The ST03 scenario
disables SID 0 at OBT 100020, enables SID 11 at 100030 and changes SID 10's
interval to two seconds at 100040. A report at a command's exact second can
precede command execution depending on task dispatch order.

Run `python3 tests/run_taste_housekeeping_smoke.py` after building, with no
other demo instance. It runs the full ST03 scenario for 49 seconds and checks
TM[3,25] values, repeated ADC sampling, disable/enable behavior, and the
changed SID 10 reporting interval. Older GUI smoke tests require a model
with the IRQ GUI and are not applicable to this deployment.

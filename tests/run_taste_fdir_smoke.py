#!/usr/bin/env python3
"""Run after make with FDIR selected and no other demo instance (about 87 s)."""
from collections import Counter
from pathlib import Path
import re
import subprocess
import tempfile

root = Path(__file__).resolve().parents[1]
with tempfile.TemporaryFile(mode="w+") as log:
    app = subprocess.Popen(["stdbuf", "-oL", str(root / "work/binaries/demo")],
                           stdout=log, stderr=subprocess.STDOUT, cwd=root)
    try:
        try:
            app.wait(timeout=87)
            raise AssertionError("application exited before the scenario completed")
        except subprocess.TimeoutExpired:
            pass
    finally:
        app.terminate()
        try:
            app.wait(timeout=3)
        except subprocess.TimeoutExpired:
            app.kill()
            app.wait()
        log.seek(0)
        output = log.read()
        print(output)

commands = Counter(re.findall(r"GSS Tx TC\[(\d+,\d+)\]", output))
assert commands == Counter({"20,3": 2, "12,5": 1, "19,1": 1,
                            "5,5": 2, "19,4": 1, "12,1": 1}), commands
reports = Counter(re.findall(r"GSS Rx TM \[(\d+,\d+)\]", output))
# Eight ground commands and one onboard recovery action. The latter has no
# extra acceptance report because it was validated when installed.
assert reports["1,1"] == 8, reports
assert reports["1,3"] == reports["1,7"] == 9, reports
assert not any(reports[k] for k in ("1,2", "1,4", "1,8")), reports
assert reports["12,12"] == 2 and reports["5,4"] == 1, reports

normal = re.search(
    r"GSS Rx TM \[12,12\]\s+PMONID = 0 PID 15 Check Limits value = 5 "
    r"limit = 1 prev status Unchecked current status Within Limits OBT = (\d+)",
    output)
fault = re.search(
    r"GSS Rx TM \[12,12\]\s+PMONID = 0 PID 15 Check Limits value = 99 "
    r"limit = 20 prev status Within Limits current status Above High Limit OBT = (\d+)",
    output)
assert normal and fault, "missing or incorrect monitoring transition payload"
assert 100072 <= int(normal[1]) <= 100075, normal[0]
assert 100080 <= int(fault[1]) <= 100083, fault[0]
event = re.search(
    r"GSS Rx TM \[5,4\] High Severity Anomaly EvID 0x4002\s+PID 15 = 99 High Limit = 20",
    output)
assert event, "missing or incorrect high-limit event payload"
assert output.count("Device Off") == 1, "recovery did not execute exactly once"
assert normal.start() < fault.start() < event.start() < output.index("Device Off")
assert "GSS Rx TM [1,7]" in output[output.index("Device Off"):]
assert "runtime error:" not in output and "AddressSanitizer" not in output
print("PASS: 8 commands, 2 monitor transitions, event 0x4002, one device-off action, 29 test TM packets")

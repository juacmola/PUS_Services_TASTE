#!/usr/bin/env python3
"""Run after make with ST03 selected and no other demo instance (about 49 s)."""
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
            app.wait(timeout=49)
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

# OBT is printed by TCManager; same-second thread ordering may differ by a tick.
obt = None
reports = {0: [], 10: [], 11: []}
values = {0: [], 10: [], 11: []}
for line in output.splitlines():
    clock = re.search(r"Current OBT is = (\d+)", line)
    if clock:
        obt = int(clock[1])
    report = re.search(r"GSS Rx TM \[3,25\] SID (\d+) Param Values \{([^}]+)\}", line)
    if report and int(report[1]) in reports:
        sid = int(report[1])
        assert obt is not None, "report arrived before first emulated second"
        reports[sid].append(obt)
        values[sid].append(report[2].split(","))
for subtype in (6, 5, 31):
    assert f"GSS Tx TC[3,{subtype}]" in output, "ST03 scenario not selected or not complete"
assert output.count("GSS Rx TM [1,7]") >= 3, "programmed commands did not complete"
assert "GSS Rx TM [1,4]" not in output, "execution failure"
assert "GSS Rx TM [1,2]" not in output, "acceptance failure"
assert len(reports[0]) >= 8 and len(reports[10]) >= 10 and len(reports[11]) >= 2, reports
assert all(len(v) == 5 for v in values[0]), values[0]
assert all(len(v) == 3 for v in values[10]), values[10]
assert all([int(x, 16) for x in v] == [5, 6, 7] for v in values[10]), values[10]
assert len({tuple(v) for v in values[0]}) > 1, "ADC values were not sampled periodically"
assert max(reports[0]) <= 100021, "SID 0 continued after disable"
assert min(reports[11]) >= 100030, "SID 11 emitted before enable"
# Avoid the command/callback boundary when checking the changed interval.
early = [t for t in reports[10] if 100004 <= t <= 100018]
late = [t for t in reports[10] if t >= 100042]
assert len(early) >= 3 and all(3 <= b-a <= 5 for a, b in zip(early, early[1:])), early
assert len(late) >= 3 and all(1 <= b-a <= 3 for a, b in zip(late, late[1:])), late
print("PASS: periodic TM[3,25] values, SID disable/enable, and interval update")

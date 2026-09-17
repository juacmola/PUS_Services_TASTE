#!/usr/bin/env python3
"""Run after make with ST01/ST17 selected and no other demo instance (18 s)."""
from collections import Counter
from pathlib import Path
import re
import subprocess

root = Path(__file__).resolve().parents[1]
proc = subprocess.Popen(['stdbuf', '-oL', str(root / 'work/binaries/demo')],
                        stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True,
                        cwd=root)
try:
    output, _ = proc.communicate(timeout=18)
    raise AssertionError('demo exited unexpectedly: ' + output)
except subprocess.TimeoutExpired:
    proc.terminate()
    try:
        output, _ = proc.communicate(timeout=5)
    except subprocess.TimeoutExpired:
        proc.kill()
        output, _ = proc.communicate()
        raise AssertionError('demo did not terminate')

reports = Counter(re.findall(r'GSS Rx TM \[(\d+,\d+)\]', output))
reports.pop('3,25', None)  # Periodic housekeeping is independent of this test.
reports.pop('5,1', None)  # Informative startup event.
assert reports == Counter({'1,1': 12, '1,3': 12, '17,2': 12,
                           '1,7': 11, '1,2': 1}), (reports, output)
obt = None
burst_acceptance = []
for line in output.splitlines():
    timestamp = re.search(r'Current OBT is = (\d+)', line)
    if timestamp:
        obt = int(timestamp[1])
    if obt is not None and obt >= 100012 and 'GSS Rx TM [1,1]' in line:
        burst_acceptance.append(obt)
assert len(burst_acceptance) == 10, (burst_acceptance, output)
assert max(Counter(burst_acceptance).values()) <= 2, burst_acceptance
assert burst_acceptance[-1] - burst_acceptance[0] >= 4, burst_acceptance
print('PASS: 48 scenario TM; burst of 10 TC / 40 TM spans OBT',
      burst_acceptance[0], 'to', burst_acceptance[-1])

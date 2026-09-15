#!/usr/bin/env python3
"""Run after make, with no other demo instance running. No GUI needed."""
from pathlib import Path
import subprocess
root = Path(__file__).resolve().parents[1]
proc = subprocess.Popen(['stdbuf', '-oL', str(root / 'work/binaries/demo')],
                        stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
try:
    output, _ = proc.communicate(timeout=5)
    raise AssertionError('demo exited unexpectedly: ' + output)
except subprocess.TimeoutExpired:
    proc.terminate()
    output, _ = proc.communicate(timeout=5)
for expected in ['GSS Tx TC[17,1]', 'GSS Rx TM [1,1]',
                 'GSS Rx TM [17,2]', 'GSS Rx TM [1,7]']:
    assert expected in output, output
print('PASS: headless emu_gss transmission, acceptance, reply and completion')

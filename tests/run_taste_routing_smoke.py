#!/usr/bin/env python3
"""Send GUI commands through the built TASTE queues and check execution telemetry."""
import ctypes
from pathlib import Path
import subprocess
import tempfile
import time

root = Path(__file__).resolve().parents[1]

class Telecommand(ctypes.Structure):
    _fields_ = [('service_type', ctypes.c_uint64),
                ('subservice_type', ctypes.c_uint64),
                ('param', ctypes.c_ubyte * 3)]

api = ctypes.CDLL(str(root / 'work/binaries/irq_GUI/PythonAccess.so'))
api.SendTC_newTC.argtypes = [ctypes.c_void_p]
api.SendTC_newTC.restype = ctypes.c_int
with tempfile.TemporaryFile(mode='w+') as log:
    app = subprocess.Popen(['stdbuf', '-oL', str(root / 'work/binaries/demo')],
                           stdout=log, stderr=subprocess.STDOUT, cwd=root)
    try:
        time.sleep(2)
        assert app.poll() is None, 'TASTE application failed during startup'
        for service, subtype in [(3, 5), (20, 1), (17, 1), (255, 1)]:
            tc = Telecommand(service, subtype, (ctypes.c_ubyte * 3)(1, 0, 0))
            assert api.SendTC_newTC(ctypes.byref(tc)) == 0
            time.sleep(1)
        assert app.poll() is None, 'TASTE application stopped during delivery'
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
    commands = output.split('[TCManager] A new TC was received')[1:]
    assert len(commands) == 4, 'unexpected number of received commands'
    assert 'GSS Rx TM [1,7]' in commands[0], 'HK command did not complete'
    assert 'GSS Rx TM [20,2]' in commands[1], 'service-20 get-parameter command did not execute'
    assert 'GSS Rx TM [1,7]' in commands[1], 'service-20 command did not complete'
    assert 'GSS Rx TM [17,2]' in commands[2], 'priority command did not execute'
    assert 'GSS Rx TM [1,2]' in commands[3], 'invalid command was not rejected'
print('PASS: GUI -> TCManager -> HK/FDIR, BKG and priority execution; invalid TC rejected')

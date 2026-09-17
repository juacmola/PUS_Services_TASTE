#!/usr/bin/env python3
"""Exercise the real TASTE/PUS bridge with ASan/UBSan; run make first."""
from pathlib import Path
from collections import Counter
import re
import subprocess
import tempfile

root = Path(__file__).resolve().parents[1]
legacy = root / 'work/asw_pus_rtems_5_0_leon3'
bridge = root / 'work/legacy/implem/default/CPP/src'
dirs = [legacy / 'taste_linux', *legacy.glob('llsw/emu_*/src')]
dirs += [legacy / 'llsw' / d / 'src' for d in
         ['tc_queue_drv', 'tc_rate_ctrl', 'tmtc_dyn_mem', 'device_drv', 'obt_drv']]
dirs += list(legacy.glob('service_libraries/pus_services/*/src'))
dirs += [legacy / 'service_libraries' / d / 'src' for d in
         ['pus_services', 'ccsds_pus', 'serialize', 'crc']]
dirs += [legacy / 'asw/dataclasses' / d / 'src' for d in
         ['CDTCHandler', 'CDTCMemDescriptor', 'CDEvAction']]
includes = [legacy, bridge, root / 'work/dataview/C',
            *legacy.glob('llsw/*/include'),
            *legacy.glob('service_libraries/*/include'),
            *legacy.glob('service_libraries/pus_services/*/include')]
with tempfile.TemporaryDirectory(prefix='sctre-routing-') as tmp:
    exe = Path(tmp) / 'routing_test'
    subprocess.run(['g++', '-std=c++17', '-pthread', '-DGENERIC_LINUX_TARGET',
                    '-fsanitize=address,undefined', '-g',
                    '-ffunction-sections', '-fdata-sections', '-Wl,--gc-sections',
                    '-Wl,--wrap=_ZN7Pr_Time7GetTimeEv',
                    *['-I' + str(d) for d in includes],
                    str(root / 'tests/legacy_routing_test.cc'), str(bridge / 'legacy.cc'),
                    *[str(p) for d in dirs for p in sorted(d.glob('*.cc'))],
                    '-o', str(exe)], check=True)
    result = subprocess.run([str(exe)], check=True, timeout=20,
                            text=True, stdout=subprocess.PIPE)
    burst = result.stdout.split('RATE_BURST_BEGIN', 1)[1].split('RATE_BURST_END', 1)[0]
    reports = Counter(re.findall(r'GSS Rx TM \[(\d+,\d+)\]', burst))
    # Ignore optional periodic housekeeping output from the selected scenario.
    reports.pop('3,25', None)
    assert reports == Counter({'1,1': 10, '1,3': 10, '17,2': 10, '1,7': 10}), reports
print('PASS: receive, routing, delayed payload delivery, rejection, bounds and pool ownership')

print('PASS: 10 queued TC produce 40 TM over 4 simulated seconds; retries preserve the queue')

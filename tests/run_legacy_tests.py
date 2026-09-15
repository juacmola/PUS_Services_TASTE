#!/usr/bin/env python3
"""Compile and exercise Linux primitives and known PUS wire-format vectors."""
from pathlib import Path
import subprocess
import tempfile

root = Path(__file__).resolve().parents[1]
legacy = root / "work/asw_pus_rtems_5_0_leon3"
with tempfile.TemporaryDirectory(prefix="sctre-test-") as tmp:
    exe = Path(tmp) / "legacy_test"
    subprocess.run([
        "g++", "-std=c++17", "-pthread", "-DGENERIC_LINUX_TARGET",
        "-fsanitize=address,undefined", "-g", "-I" + str(legacy),
        str(root / "tests/legacy_linux_test.cc"),
        str(legacy / "service_libraries/serialize/src/serialize.cc"),
        str(legacy / "taste_linux/legacy_primitives.cc"),
        "-o", str(exe),
    ], check=True)
    subprocess.run([str(exe)], check=True, timeout=10)
print("PASS: fixed-width types, PUS wire format, recursive locking and monotonic time")

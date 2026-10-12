#!/usr/bin/env python3
"""Apply the native patch stack once, for both Make and Meson."""
from pathlib import Path
import subprocess


def main():
    root = Path(__file__).resolve().parent.parent
    marker = root / 'patch.done'
    if marker.exists():
        return
    patches = sorted((root / 'patches').glob('*.patch'))
    if not patches:
        raise SystemExit('ghidra-native: no patches found')
    for patch in patches:
        print('Applying ' + patch.name, flush=True)
        subprocess.run(['git', 'apply', '--whitespace=nowarn', str(patch)], cwd=root, check=True)
    marker.touch()


if __name__ == '__main__':
    main()

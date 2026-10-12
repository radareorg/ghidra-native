#!/usr/bin/env python3
"""Print a source set from sources.mk for build systems other than Make."""
from pathlib import Path
import sys


def sources(name, definitions):
    for item in definitions[name].split():
        if item.startswith('$(') and item.endswith(')'):
            yield from sources(item[2:-1], definitions)
        else:
            yield item


if __name__ == '__main__':
    manifest = Path(__file__).resolve().parent.parent / 'sources.mk'
    definitions = {}
    for line in manifest.read_text(encoding='utf-8').replace('\\\n', ' ').splitlines():
        name, separator, value = line.partition('=')
        if separator:
            definitions[name.strip()] = value.strip()
    if len(sys.argv) != 2 or sys.argv[1] not in definitions:
        sys.exit('usage: sources.py <source-set name from sources.mk>')
    print(' '.join(sources(sys.argv[1], definitions)))

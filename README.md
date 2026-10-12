# ghidra-native

[![ci](https://github.com/radareorg/ghidra-native/actions/workflows/ci.yml/badge.svg?branch=master)](https://github.com/radareorg/ghidra-native/actions/workflows/ci.yml)

This repository contains the native parts of ghidra, aiming to be used from r2ghidra:

* Sleigh compiler
* Decompiler

Additionally it also contains the processors needed for it to work.

This repository is mean to be manually updated from time to time.

Reasons behind forking ghidra decompiler code:

* Reduce the amount of noise and confusing subdirectories
* Ease testing and better integration with r2ghidra
* Improve patch maintainance workflows
* Reduce repository size shipping only the native parts (512MB -> 15MB)
* Update processor sleigh and decompiler logic separately
* Add 3rd party processors easily

Unit tests for the decompiler patches live in `src/unittests/` and are run
with `make test` (meson/ninja required); see `tests/README.md`.

## Building and embedding

Python 3, Git, Meson, Ninja, and a C++14 compiler are required. Make and Meson
use the same patch runner, which writes `patch.done` after applying the complete
stack. Distribution archives include this marker and can be built without Git.

```
meson setup build -Dtests=true
meson compile -C build
meson test -C build --print-errorlogs
```

`make` builds the libraries and Sleigh compiler; `make test` enables and runs
the regression tests. Meson reads the project version directly from `VERSION`.

Meson consumers can use `subproject('ghidra-native')` and its `ghidra_dep`
dependency, `sleighc_exe` target, `processor_dir`, and `sleigh_compile` helper.
`ghidra_embedded_sources` contains the native source files for frontends that
compile the decompiler into their own library. It excludes the Ghidra command
entry point and includes the native integration sources.

Make consumers can include `sources.mk` and use `GHIDRA_EMBEDDED_SRCS` or the
individual source sets. Other build integrations can run
`python3 scripts/sources.py GHIDRA_EMBEDDED_SRCS` to read the same manifest.

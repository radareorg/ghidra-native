# ghidra-native unit tests

Focused regression tests for the decompiler patches in `patches/`.
The tests build the vendored decompiler sources with meson and run the
tests from `src/unittests/` with the small driver in `tests/main.cc`.

The tests in `src/unittests/` are picked up by the upstream
`src/decompiler/Makefile` as well (its `UNITTEST_SOURCE` macro looks in
`../unittests`), so `make -C src/decompiler test` builds the same tests
on systems with a full GNU toolchain and BFD.

## Running

The tests must run against the *patched* sources.  `make test` applies
the patch stack automatically and then runs meson:

```
make test
```

or manually:

```
make patch
meson setup build -Dtests=true
meson test -C build --print-errorlogs
```

On Windows, run the commands from a Visual Studio developer prompt
(`vcvars64.bat`) so that meson selects MSVC:

```
call "C:\Program Files\Microsoft Visual Studio\18\Professional\VC\Auxiliary\Build\vcvars64.bat"
meson setup build -Dtests=true
meson test -C build --print-errorlogs
```

If the system has no zlib development package, meson falls back to the
`zlib.wrap` file in `subprojects/`.

## Tests

`src/unittests/paramactive.cc`
: `ParamActive::whichTrial` regression tests.  The one-byte cases are
  the regression from rizinorg/rz-ghidra#385: the original code returned
  `-1` as soon as the first trial did not overlap a one-byte access,
  which made callers register duplicate trials or index the trial vector
  with `-1`.

`src/unittests/pcodeinject.cc`
: Dynamic p-code injection tests.  A `<pcode inject="..." dynamic="true"/>`
  declaration needs a front-end (Ghidra's Java side) to supply the
  payload; without one, `InjectPayloadDynamic::inject` throws
  `Missing dynamic inject`, so the shipped processor specs must not
  declare dynamic injects that native-only users cannot service.

## Manual Dalvik integration repro

The Dalvik item of PR #26 is about `<pcode inject="uponentry"
dynamic="true"/>` and `<callotherfixup targetop="moveRangeToIV">` being
removed from `src/Processors/Dalvik/data/languages/Dalvik_Base.cspec`.
To check the behaviour end to end with an r2ghidra build:

1. Get a small DEX (e.g. `dex/Hello.dex` or `dex/dex38.dex` from
   https://github.com/radareorg/radare2-testbins).
2. Decompile the methods of the file with r2ghidra:

   ```
   radare2 -q -a dalvik -b 32 -e io.cache=true -c 'aa; pdg @@f' Hello.dex
   ```

   With the patched (stripped) specification the decompiler must produce
   output for every method without reporting `Missing dynamic inject` or
   asserting.  r2ghidra itself provides native implementations for the
   `moveRangeToIV` userop (`R2DalvikPcodeInjectLibrary`), so leaving the
   userop unresolved is handled gracefully.

3. To exercise the other side, point `SLEIGHHOME` at a stock Ghidra
   installation (whose `Dalvik_Base.cspec` still has the dynamic
   declarations) and repeat; r2ghidra services `uponentry` and
   `moveRangeToIV` natively in that configuration as well.

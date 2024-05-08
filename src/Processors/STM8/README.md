# ghidra_STM8

Ghidra STM8 processor module

## Installation

### Easy way

just copy files to
`$(GHIDRA_HOME)\Ghidra\Extensions\`

### Long way

In this case you also build an analyzer plugin that automatically assigns the proper calling convention. This is very useful for big binaries.

* run `# GHIDRA_INSTALL_DIR=$(full path to ghidra installation) gradle`
* open Ghidra
* in the project selection window click File -> Install Extension
* select `lib/ghidra_STM8.jar` that was built by gradle


## Notes

STM8 uses two kinds of pointers: standard 16-bit, that can deal with RAM, I/O area and the bottom of Flash and 'far' 24-bit pointers that can address all memory.

In Ghidra far pointers can be declared as `byte *24`, `my_struct *24`, etc.

Functions that called by `CALLF` should be declared as `__farcall`. Standard ones, that called by `CALL`, should be declared as `__stdcall` (default behavior).


If the flash image is larger than 32 kbytes, use `STM8:BE:24` language, otherwise either option can be used (but `STM8:BE:16` gives clearer output).

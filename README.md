ghidra-native
============= 

This repository contains the native parts of ghidra, aiming to be used from r2ghidra:

* Sleigh compiler
* Decompiler

Additionally it also contains the processors needed for it to work.

This repository is updated manually from time to time.

Reasons for this:

* Ease testing and better integration with r2ghidra
* Improve patch maintainance workflows
* Reduce repository size shipping only the native parts (512MB -> 20MB)

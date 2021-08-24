ghidra-native
============= 

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

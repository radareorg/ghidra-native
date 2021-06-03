all:
	
sync: sync-processors sync-decompiler

patch:
	for a in $(shell ls patches/*.patch | sort -n) ; do patch -p1 < $$a ; done

sync-decompiler decompiler-sync: ghidra
	rm -rf src/decompiler
	cp -rf ghidra/Ghidra/Features/Decompiler/src/decompile/cpp src/decompiler

sync-processors processors-sync: ghidra
	rm -rf src/Processors
	cp -rf ghidra/Ghidra/Processors src/Processors

ghidra:
	git clone https://github.com/NationalSecurityAgency/ghidra

.PHONY: all sync sync-decompiler sync-processors

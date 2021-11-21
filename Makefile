all:
	
update sync: sync-processors sync-decompiler

patch: patch.done

patch.done:
	for a in $(shell ls patches/*.patch | sort -n) ; do patch -p1 < $$a ; done
	touch patch.done

massage:
	mkdir -p /tmp/patches
	git reset --hard
	for a in $(shell ls patches/*.patch | sort -n) ; do patch -p1 < $$a ; git diff > /tmp/$$a ; git reset --hard ; done
	mv /tmp/patches/* patches
	

sync-decompiler decompiler-sync: ghidra
	rm -rf src/decompiler
	cp -rf ghidra/Ghidra/Features/Decompiler/src/decompile/cpp src/decompiler
	rm -rf src/Processor/*/src

V=$(shell cat VERSION)
D=ghidra-native-$(V)

dist:
	git clone . $(D)
	make -C $(D) patch
	rm -rf $(D)/.git
	zip -r $(D).zip $(D)
	rm -rf $(D)

sync-processors processors-sync: ghidra
	rm -rf src/Processors
	cp -rf ghidra/Ghidra/Processors src/Processors
	$(MAKE) sync-stm8

sync-stm8:
	rm -rf ghidra_STM8
	git clone https://github.com/esaulenka/ghidra_STM8
	mkdir -p src/Processors/STM8
	cp -rf ghidra_STM8/* src/Processors/STM8

ghidra:
	git clone https://github.com/NationalSecurityAgency/ghidra

.PHONY: all sync sync-decompiler sync-processors

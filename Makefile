all:

clean:
	rm -f patch.done

mrproper: clean
	git reset --hard
	git clean -xdf

update sync: sync-processors sync-decompiler

patch: patch.done

patch.done:
	for a in $(shell ls patches/*.patch | sort -n) ; do echo "patch -p1 < $$a" ; patch -p1 < $$a ; done
	touch patch.done

massage:
	mkdir -p /tmp/patches
	git reset --hard
	for a in $(shell ls patches/*.patch | sort -n) ; do echo "patch -p1 < $$a" ; patch -p1 < $$a ; git diff > /tmp/$$a ; git reset --hard ; done
	mv /tmp/patches/* patches


sync-ghidra ghidra-sync sync-decompiler decompiler-sync: ghidra
	rm -rf src/decompiler
	cp -rf ghidra/Ghidra/Features/Decompiler/src/decompile/cpp src/decompiler
	rm -rf src/Processor/*/src
	rm -rf src/Processors/*/src

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
	$(MAKE) sync-hexagon
	$(MAKE) sync-wasm
	$(MAKE) sync-sbpf

sync-sbpf:
	rm -rf ghidra_sBPF
	git clone https://github.com/daog1/ghidra_sbpf
	mkdir -p src/Processors/sBPF
	cp -rf ghidra_sbpf/* src/Processors/sBPF

sync-wasm:
	rm -rf ghidra_wasm
	git clone https://github.com/andr3colonel/ghidra_wasm
	mkdir -p src/Processors/wasm
	cp -rf ghidra_wasm/* src/Processors/wasm

sync-stm8:
	rm -rf ghidra_STM8
	git clone https://github.com/esaulenka/ghidra_STM8
	mkdir -p src/Processors/STM8
	cp -rf ghidra_STM8/* src/Processors/STM8

sync-hexagon:
	git clone --depth=1 https://github.com/toshipiazza/ghidra-plugin-hexagon/
	mkdir -p src/Processors/hexagon/data/languages
	cp ghidra-plugin-hexagon/Ghidra/Processors/Hexagon/data/languages/* \
		src/Processors/hexagon/data/languages
	rm -rf ghidra-plugin-hexagon

ghidra:
	git clone https://github.com/NationalSecurityAgency/ghidra

.PHONY: all sync sync-decompiler sync-processors

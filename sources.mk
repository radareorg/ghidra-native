# Shared native source sets for Make, Meson, and embedded consumers.

GHIDRA_BASE_SRCS = \
	marshal.cc \
	space.cc \
	float.cc \
	address.cc \
	pcoderaw.cc \
	translate.cc \
	opcodes.cc \
	globalcontext.cc \
	xml.cc

GHIDRA_DECOMPILER_SRCS = \
	capability.cc \
	architecture.cc \
	options.cc \
	graph.cc \
	cover.cc \
	block.cc \
	cast.cc \
	typeop.cc \
	database.cc \
	cpool.cc \
	comment.cc \
	stringmanage.cc \
	modelrules.cc \
	fspec.cc \
	action.cc \
	loadimage.cc \
	varnode.cc \
	op.cc \
	type.cc \
	variable.cc \
	varmap.cc \
	jumptable.cc \
	emulate.cc \
	emulateutil.cc \
	flow.cc \
	userop.cc \
	expression.cc \
	multiprecision.cc \
	funcdata.cc \
	funcdata_block.cc \
	funcdata_varnode.cc \
	unionresolve.cc \
	funcdata_op.cc \
	pcodeinject.cc \
	heritage.cc \
	prefersplit.cc \
	rangeutil.cc \
	ruleaction.cc \
	subflow.cc \
	transform.cc \
	blockaction.cc \
	merge.cc \
	double.cc \
	coreaction.cc \
	condexe.cc \
	override.cc \
	dynamic.cc \
	crc32.cc \
	prettyprint.cc \
	printlanguage.cc \
	printc.cc \
	printjava.cc \
	memstate.cc \
	opbehavior.cc \
	paramid.cc \
	signature.cc \
	constseq.cc \
	bitfield.cc

GHIDRA_INTEGRATION_SRCS = \
	ghidra_arch.cc \
	loadimage_ghidra.cc \
	typegrp_ghidra.cc \
	database_ghidra.cc \
	ghidra_context.cc \
	cpool_ghidra.cc \
	comment_ghidra.cc \
	inject_ghidra.cc \
	ghidra_translate.cc \
	string_ghidra.cc

GHIDRA_SLEIGH_SRCS = \
	sleigh.cc \
	sleigh_arch.cc \
	inject_sleigh.cc \
	pcodecompile.cc \
	sleighbase.cc \
	slghsymbol.cc \
	slghpatexpress.cc \
	slghpattern.cc \
	semantics.cc \
	context.cc \
	slaformat.cc \
	compression.cc \
	filemanage.cc \
	pcodeparse.cc \
	grammar.cc

GHIDRA_LIBDECOMP_SRCS = \
	libdecomp.cc

GHIDRA_SLEIGH_COMPILER_SRCS = \
	slgh_compile.cc \
	slghparse.cc \
	slghscan.cc

GHIDRA_EMBEDDED_SRCS = $(GHIDRA_BASE_SRCS) $(GHIDRA_DECOMPILER_SRCS) $(GHIDRA_SLEIGH_SRCS) $(GHIDRA_LIBDECOMP_SRCS) $(GHIDRA_INTEGRATION_SRCS)

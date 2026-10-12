project('ghidra-native-tests', 'cpp',
  meson_version : '>=0.60.0',
  default_options : ['cpp_std=c++14', 'warning_level=0', 'werror=false'])

# Unit tests for the decompiler sources vendored in src/decompiler.
#
# The tests build the decompiler library sources (the source set the
# upstream Makefile collects into libdecomp.a, minus the BFD load image
# and the console/debug interface files) together with the test driver
# tests/main.cc and the tests in src/unittests/.
#
# The tests must run against *patched* sources: run `make patch` first
# (the Makefile `test` target does this automatically).

cpp = meson.get_compiler('cpp')

zlib = dependency('zlib', required : false)
if not zlib.found()
  zlib_proj = subproject('zlib', default_options : ['default_library=static'])
  zlib = zlib_proj.get_variable('zlib_dep')
endif

extra_args = []
if cpp.get_id() == 'msvc'
  extra_args += ['-D_WINDOWS', '-D_WIN32']
endif

base_sources = files(
  '../src/decompiler/marshal.cc',
  '../src/decompiler/space.cc',
  '../src/decompiler/float.cc',
  '../src/decompiler/address.cc',
  '../src/decompiler/pcoderaw.cc',
  '../src/decompiler/translate.cc',
  '../src/decompiler/opcodes.cc',
  '../src/decompiler/globalcontext.cc',
  '../src/decompiler/xml.cc',
)

decompiler_sources = files(
  '../src/decompiler/capability.cc',
  '../src/decompiler/architecture.cc',
  '../src/decompiler/options.cc',
  '../src/decompiler/graph.cc',
  '../src/decompiler/cover.cc',
  '../src/decompiler/block.cc',
  '../src/decompiler/cast.cc',
  '../src/decompiler/typeop.cc',
  '../src/decompiler/database.cc',
  '../src/decompiler/cpool.cc',
  '../src/decompiler/comment.cc',
  '../src/decompiler/stringmanage.cc',
  '../src/decompiler/modelrules.cc',
  '../src/decompiler/fspec.cc',
  '../src/decompiler/action.cc',
  '../src/decompiler/loadimage.cc',
  '../src/decompiler/varnode.cc',
  '../src/decompiler/op.cc',
  '../src/decompiler/type.cc',
  '../src/decompiler/variable.cc',
  '../src/decompiler/varmap.cc',
  '../src/decompiler/jumptable.cc',
  '../src/decompiler/emulate.cc',
  '../src/decompiler/emulateutil.cc',
  '../src/decompiler/flow.cc',
  '../src/decompiler/userop.cc',
  '../src/decompiler/expression.cc',
  '../src/decompiler/multiprecision.cc',
  '../src/decompiler/funcdata.cc',
  '../src/decompiler/funcdata_block.cc',
  '../src/decompiler/funcdata_varnode.cc',
  '../src/decompiler/unionresolve.cc',
  '../src/decompiler/funcdata_op.cc',
  '../src/decompiler/pcodeinject.cc',
  '../src/decompiler/heritage.cc',
  '../src/decompiler/prefersplit.cc',
  '../src/decompiler/rangeutil.cc',
  '../src/decompiler/ruleaction.cc',
  '../src/decompiler/subflow.cc',
  '../src/decompiler/transform.cc',
  '../src/decompiler/blockaction.cc',
  '../src/decompiler/merge.cc',
  '../src/decompiler/double.cc',
  '../src/decompiler/coreaction.cc',
  '../src/decompiler/condexe.cc',
  '../src/decompiler/override.cc',
  '../src/decompiler/dynamic.cc',
  '../src/decompiler/crc32.cc',
  '../src/decompiler/prettyprint.cc',
  '../src/decompiler/printlanguage.cc',
  '../src/decompiler/printc.cc',
  '../src/decompiler/printjava.cc',
  '../src/decompiler/memstate.cc',
  '../src/decompiler/opbehavior.cc',
  '../src/decompiler/paramid.cc',
  '../src/decompiler/inject_sleigh.cc',
  '../src/decompiler/bitfield.cc',
  '../src/decompiler/constseq.cc',
  '../src/decompiler/signature.cc',
  '../src/decompiler/sleigh.cc',
  '../src/decompiler/sleigh_arch.cc',
  '../src/decompiler/pcodecompile.cc',
  '../src/decompiler/sleighbase.cc',
  '../src/decompiler/slghsymbol.cc',
  '../src/decompiler/slghpatexpress.cc',
  '../src/decompiler/slghpattern.cc',
  '../src/decompiler/semantics.cc',
  '../src/decompiler/context.cc',
  '../src/decompiler/slaformat.cc',
  '../src/decompiler/compression.cc',
  '../src/decompiler/filemanage.cc',
  '../src/decompiler/pcodeparse.cc',
  '../src/decompiler/grammar.cc',
)

unit_test_sources = files(
  'main.cc',
  '../src/unittests/paramactive.cc',
  '../src/unittests/pcodeinject.cc',
)

decompiler_test = executable('decompiler_test',
  base_sources + decompiler_sources + unit_test_sources,
  include_directories : include_directories('../src/decompiler'),
  dependencies : zlib,
  cpp_args : extra_args,
)

test('ghidra-native-unittests', decompiler_test)

decompiler_test = executable('decompiler_test',
  'main.cc',
  '../src/unittests/paramactive.cc',
  '../src/unittests/pcodeinject.cc',
  include_directories: incs,
  dependencies: zlib,
  link_with: [ghidra_base_static, ghidra_decompiler_static, slgh_static])

test('ghidra-native-unittests', decompiler_test)

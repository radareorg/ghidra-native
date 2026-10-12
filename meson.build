project('ghidra-native', 'cpp',
  meson_version: '>=0.60.0',
  version: files('VERSION')[0],
  license: 'Apache-2.0',
  default_options: ['cpp_std=c++14', 'werror=false'])

python = find_program('python3', 'python', required: true)
run_command(python, files('scripts/apply_patches.py'), check: true)

source_reader = files('scripts/sources.py')
# Track the manifest so source-set edits regenerate the build definition.
import('fs').read('sources.mk')
foreach source_set : [
  ['BASE', 'base_sources'],
  ['DECOMPILER', 'decompiler_sources'],
  ['SLEIGH', 'slgh_sources'],
  ['LIBDECOMP', 'libdecomp_sources'],
  ['INTEGRATION', 'ghidra_sources'],
  ['SLEIGH_COMPILER', 'sleigh_compiler_sources'],
]
  names = run_command(python, source_reader, 'GHIDRA_' + source_set[0] + '_SRCS', check: true).stdout().strip().split()
  sources = []
  foreach name : names
    sources += files('src/decompiler/' + name)
  endforeach
  set_variable(source_set[1], sources)
endforeach
ghidra_embedded_sources = base_sources + decompiler_sources + slgh_sources + libdecomp_sources + ghidra_sources

if meson.get_compiler('cpp').get_id() == 'msvc'
  add_project_arguments('-D_WINDOWS', '-D_WIN32', language: 'cpp')
endif

zlib = dependency('zlib', version: '>=1.2.8', required: false)
if not zlib.found()
  zlib = subproject('zlib', default_options: ['default_library=static', 'werror=false']).get_variable('zlib_dep')
endif

incs = include_directories('src/decompiler')
ghidra_base_static = static_library('base', base_sources,
  include_directories: incs, implicit_include_directories: false)
ghidra_decompiler_static = static_library('ghidra', decompiler_sources,
  dependencies: zlib, link_with: ghidra_base_static,
  include_directories: incs, implicit_include_directories: false)
slgh_static = static_library('slgh', slgh_sources,
  dependencies: zlib, link_with: ghidra_base_static,
  include_directories: incs, implicit_include_directories: false)
libdecomp_static = static_library('libdecomp', libdecomp_sources,
  dependencies: zlib, link_with: [ghidra_decompiler_static, slgh_static],
  include_directories: incs, implicit_include_directories: false)
ghidra_dep = declare_dependency(link_with: libdecomp_static,
  include_directories: incs, dependencies: zlib)
ghidra_embedded_static = static_library('ghidra-embedded', ghidra_sources,
  dependencies: zlib, link_with: libdecomp_static,
  include_directories: incs, implicit_include_directories: false)
sleighc_exe = executable('sleighc', sleigh_compiler_sources,
  dependencies: zlib, link_with: slgh_static,
  include_directories: incs, implicit_include_directories: false,
  install: true)

processor_dir = meson.current_source_dir() / 'src' / 'Processors'
sleigh_compile = files('scripts/compile_sleigh.py')

if get_option('tests')
  subdir('tests')
endif

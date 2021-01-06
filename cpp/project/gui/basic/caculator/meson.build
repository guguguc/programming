project('caculator', 'cpp', default_options: 'optimization=s')

gtkmm_dep = dependency('gtkmm-3.0')
program_name = 'caculator'
cpp_sources = [ 'caculator.cc', 'gui.cc', 'main.cc']

executable(program_name,
  cpp_sources,
  dependencies: gtkmm_dep)

project('sokolSample', 'c', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3'])

c_cmplr = meson.get_compiler('c')


subdir('cimgui')
subdir('sokol')

libs_names = [
  'GL',
  'dl',
  'm',
  'glfw3',
  'X11',
  'xi',
  'Xcursor'
]

deps = []

foreach lib : libs_names
  tmp = dependency(lib, required : false)
  if not tmp.found()
    tmp = c_cmplr.find_library(lib)
  endif
  deps += tmp
endforeach



executable('sokolsample', 
  sources : ['demo.c'],
  dependencies : [deps , sokol_dep],
#   c_args : ['-DSOKOL_IMPL', '-DSOKOL_GLCORE33'],
  install : true)


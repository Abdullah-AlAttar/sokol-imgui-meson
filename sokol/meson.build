
sokol_includes = ['.']

sokol_sources = ['sokol.c']

sokol_lib = static_library('sokol', sources : sokol_sources, dependencies : cimgui_dep)

sokol_dep = declare_dependency(include_directories : include_directories(sokol_includes),
                              link_with: sokol_lib,
                              dependencies : cimgui_dep)
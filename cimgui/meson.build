


cimgui_sources = [
    './cimgui.cpp',
    './cimgui.h',
    './imgui/imgui.cpp',
    './imgui/imgui.h',
    './imgui/imgui_widgets.cpp',
    './imgui/imgui_draw.cpp',
    './imgui/imgui_demo.cpp'
]

cimgui_includes = [
    '.'
]


cimgui_lib = static_library('cimgui', sources : cimgui_sources)

cimgui_dep = declare_dependency(include_directories : cimgui_includes, link_with : cimgui_lib)

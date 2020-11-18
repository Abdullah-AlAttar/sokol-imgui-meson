//------------------------------------------------------------------------------
//  Simple C99 cimgui+sokol starter project for Win32, Linux and macOS.
//------------------------------------------------------------------------------
#include "sokol_app.h"
#include "sokol_gfx.h"
#include "sokol_time.h"
#include "sokol_glue.h"
#include "triangle.glsl.h"
#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui.h"
#include "sokol_imgui.h"

static struct {
    sg_pipeline pip;
    sg_bindings bind;
    uint64_t laptime;
    sg_pass_action pass_action;
} state;

static void init(void) {
    sg_setup(&(sg_desc){
        .context = sapp_sgcontext()
    });
    stm_setup();
    simgui_setup(&(simgui_desc_t){ 0 });

    sg_shader shd = sg_make_shader(simple_shader_desc());

    /* a vertex buffer with 3 vertices */
    float vertices[] = {
        // positions
        -0.5f, -0.5f, 0.0f,     // bottom left
        0.5f, -0.5f, 0.0f,      // bottom right
        0.0f,  0.5f, 0.0f       // top
    };
    state.bind.vertex_buffers[0] = sg_make_buffer(&(sg_buffer_desc){
        .size = sizeof(vertices),
        .content = vertices,
        .label = "triangle-vertices"
    });

    /* create a pipeline object (default render states are fine for triangle) */
    state.pip = sg_make_pipeline(&(sg_pipeline_desc){
        .shader = shd,
        /* if the vertex layout doesn't have gaps, don't need to provide strides and offsets */
        .layout = {
            .attrs = {
                [ATTR_vs_position].format = SG_VERTEXFORMAT_FLOAT3
            }
        },
        .label = "triangle-pipeline"
    });

    /* a pass action to clear framebuffer */

    // initial clear color
    state.pass_action = (sg_pass_action) {
        .colors[0] = { .action = SG_ACTION_CLEAR,  .val = { 0.0f, 0.5f, 1.0f, 1.0 } }
    };
}

static void frame(void) {
    const int width = sapp_width();
    const int height = sapp_height();
    const double delta_time = stm_sec(stm_round_to_common_refresh_rate(stm_laptime(&state.laptime)));
    simgui_new_frame(width, height, delta_time);

    /*=== UI CODE STARTS HERE ===*/
    igSetNextWindowPos((ImVec2){10,10}, ImGuiCond_Once, (ImVec2){0,0});
    igSetNextWindowSize((ImVec2){400, 100}, ImGuiCond_Once);
    igBegin("Hello Dear ImGui!", 0, ImGuiWindowFlags_None);
    igColorEdit3("Background", &state.pass_action.colors[0].val[0], ImGuiColorEditFlags_None);
    igEnd();
    /*=== UI CODE ENDS HERE ===*/

    sg_begin_default_pass(&state.pass_action, width, height);
    sg_apply_pipeline(state.pip);
    sg_apply_bindings(&state.bind);
    sg_draw(0, 3, 1);
    simgui_render();
    sg_end_pass();
    sg_commit();
}

static void cleanup(void) {
    simgui_shutdown();
    sg_shutdown();
}

static void event(const sapp_event* ev) {
    simgui_handle_event(ev);
}

sapp_desc sokol_main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    return (sapp_desc){
        .init_cb = init,
        .frame_cb = frame,
        .cleanup_cb = cleanup,
        .event_cb = event,
        .window_title = "Hello Sokol + Dear ImGui",
        .width = 800,
        .height = 600,
    };
}

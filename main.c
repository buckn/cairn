/*
    Sokol Headers
*/
#include "sokol_audio.h"
#include "sokol_app.h"
#include "sokol_gfx.h"
#include "sokol_glue.h"

/*
    Include standard library headers
*/
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

//Math file include
#include "mat.h"

//Client state static struct
static struct {
    /* ... */

    /* input */
    bool keys_down[SAPP_MAX_KEYCODES];
    Vec2 m_pos;
    int snd_sin_wav;
} cli;

//Include renderer and sound header files
#include "ren.h"
#include "snd.h"

void init(void) {
    render_init();
    snd_init();
}

void frame(void) {
    frame_start();

    /*
        Frame drawing begins here
    */
    
    //static rect
    draw_start();
    draw_scale(1.0f, 1.0f);
    draw_pivot(0.2f, 0.0f);
    draw_dir(vec2(0.0f, 0.0f));
    draw_rad(0.1f);
    draw_color(0, 0, 255, 255);
    draw_pos_vec(mouse_pos_world(cli.m_pos));
    draw();

    /*
        Frame drawing ends here
    */

    draw_end();
}

void cleanup(void) {
    sg_shutdown();
    snd_shutdown();
}

void event(const sapp_event *ev) {
    switch (ev->type) {
    case (SAPP_EVENTTYPE_KEY_DOWN):;
        cli.keys_down[ev->key_code] = true;
        #ifndef NDEBUG
        if (ev->key_code == SAPP_KEYCODE_ESCAPE)
            sapp_request_quit();
        #endif
        break;
    case SAPP_EVENTTYPE_KEY_UP:;
        cli.keys_down[ev->key_code] = false;
        break;
    case SAPP_EVENTTYPE_MOUSE_UP:;
    case SAPP_EVENTTYPE_MOUSE_DOWN:;
    case SAPP_EVENTTYPE_MOUSE_MOVE:;
        cli.m_pos = vec2(ev->mouse_x, ev->mouse_x);
        break;
    default: ;
    };
}

sapp_desc sokol_main(int argc, char* argv[]) {
    (void)argc; (void)argv;
    return (sapp_desc){
        .sample_count = 8,
        .high_dpi = true,
        .init_cb = init,
        .frame_cb = frame,
        .cleanup_cb = cleanup,
        .event_cb = event,
        .width = 960,
        .height = 1080,
        .window_title = "cairn",
    };
}

/*
    Include standard library headers
*/
#include <math.h>
#include <assert.h>
#include <stdbool.h>

/*
    Include ren.h and mat.h
*/

#include "mat.h"
#include "ren.h"

/*
    Include csound.h
*/
#include "csound/include/csound.h"

static struct {
    /* ... */

    /* input */
    bool keys_down[SAPP_MAX_KEYCODES];
} cli;

void init(void) {
    render_init();
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
    draw_color(128, 128, 128, 255);
    draw();

    /*
        Frame drawing ends here
    */

    draw_end();
}

void cleanup(void) {
    sg_shutdown();
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
    default: ;
    };
}

sapp_desc sokol_main(int argc, char* argv[]) {
    (void)argc; (void)argv;
    return (sapp_desc){
        .sample_count = 32,
        .high_dpi = true,
        .init_cb = init,
        .frame_cb = frame,
        .cleanup_cb = cleanup,
        .event_cb = event,
        .width = 1920,
        .height = 1080,
        .window_title = "Cairn",
    };
}

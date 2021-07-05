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
#include <time.h>

//math include
#include "mat.h"

//Client state static struct
static struct {
    /* input */
    bool keys_down[SAPP_MAX_KEYCODES];
    Vec2 m_pos;

    /* sound */
    int snd_sin_wav;
} cli;

//sound include
#include "snd.h"

//renderer include
#include "ren.h"

//entities include
#include "ent.h"

void init(void) {
    render_init();
    snd_init();

    //make new rock entity
    add_ent(stn(vec2(0, 0)));
}

void frame(void) {
    clock_t current_ticks = clock();

    //entities physics tick
    tick_all_ents();

    frame_start();

    //render all entities
    rndr_all_ents();

    draw_end();

    clock_t delta_ticks = clock() - current_ticks; //the time, in ms, that took to render the scene
    clock_t fps = 0;
    if(delta_ticks > 0) {
        fps = CLOCKS_PER_SEC / delta_ticks;
    }
    printf("fps: %lu\n", fps);
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
        cli.m_pos = vec2(ev->mouse_x, ev->mouse_y);
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

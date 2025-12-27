#include "engine.h"
#include "window.h"
#include "render.h"
#include "game.h"

static int running = 1;

void engine_init(int width, int height, const char* title) {
    window_init(width, height, title);
    render_init();
}

void engine_run() {
    while (running && !window_should_close()) {
        double dt = window_get_delta_time();

        render_clear();
        
        game_update(dt);

        window_swap_buffers();
        window_poll_events();
    }
}

void engine_shutdown() {
    render_shutdown();
    window_shutdown();
}
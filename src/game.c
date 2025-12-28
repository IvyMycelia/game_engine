#include "game.h"

#include <stdio.h>

void game_update(double delta_time) {
    Rect test_object = draw_button((Rect){-0.5f, -0.5f, 1.0f, 0.5f}, 1.0f, (Color){1.0f, 0.0f, 0.0f, 1.0f}, (Color){0.0f, 1.0f, 0.0f, 1.0f}, "Engine Button Test", (Color){1.0f, 1.0f, 1.0f, 1.0f});
    draw_text(0.0f, 0.0f, "Game Engine Running...", (Color){1.0f, 1.0f, 1.0f, 1.0f}, 1.0f);
}
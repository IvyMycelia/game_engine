#include "game.h"

#include <stdio.h>

void game_update(double delta_time) {
    Rect test_object = draw_button(-0.5f, -0.5f, 1.0f, 0.5f, 1.0f, (Color){1.0f, 0.0f, 0.0f, 1.0f}, (Color){0.0f, 1.0f, 0.0f, 1.0f}, "Game Engine Button Test", (Color){1.0f, 1.0f, 1.0f, 1.0f});
    Tri test_triangle = draw_triangle(-1.5f, -1.5f, -1.5f, 0.0f, -0.5f, 0.0f, (Color){0.0f, 1.0f, 0.0f, 1.0f}, 1.0f, (Color){0.0f, 1.0f, 1.0f, 1.0f});
    Rect test_rect = draw_rectangle(-0.25f, -0.25f, 0.5f, 0.5f, (Color){0.0f, 0.0f, 1.0f, 1.0f}, 2.0f, (Color){1.0f, 1.0f, 0.0f, 1.0f});
    draw_text(-0.5f, 0.5f, "Game Engine Running...", (Color){1.0f, 1.0f, 1.0f, 1.0f}, 0.1f);
}
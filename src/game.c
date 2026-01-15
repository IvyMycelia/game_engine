#include "game.h"

#include <stdio.h>

Shape test_rect;
Shape test_triangle;
Shape test_circle;

void game_start() {
    test_triangle = draw_triangle(
        (Vec2){-1.5f, -1.5f},
        (Vec2){-1.5f, 0.0f},
        (Vec2){ -0.5f, 0.0f},
        (Color){0.0f, 1.0f, 0.0f, 1.0f}
    );

    test_circle = draw_circle(-0.75f, 0.5f, 0.1f, (Color){0.0f, 0.5f, 1.0f, 1.0f});
    test_rect = draw_rectangle(-0.25f, -0.25f, 0.5f, 0.5f, (Color){0.0f, 0.0f, 1.0f, 1.0f});
}

double fps = 0.0f;
void game_update(double delta_time) {
    // Render the primitive shapes
    render_circle(&test_circle, 10, 2.0f, (Color){1.0f, 0.5f, 0.5f, 1.0f});
    render_polygon(&test_triangle, 1.0f, (Color){0.0f, 1.0f, 1.0f, 1.0f});
    render_rectangle(&test_rect, 2.0f, (Color){1.0f, 1.0f, 0.0f, 1.0f});
    draw_text(-0.5f, 0.5f, "Game Engine Running...", (Color){1.0f, 1.0f, 1.0f, 1.0f}, 0.1f);
    
    // FPS
    double alpha = 0.01f;
    fps = fps * (1.0 - alpha) + (1.0 / delta_time) * alpha;
    char fps_text[64];
    snprintf(fps_text, sizeof(fps_text), "FPS: %.1lf", fps);
    draw_text(-0.95f, 0.9f, fps_text, (Color){0.0f, 1.0f, 0.0f, 1.0f}, 0.1f);

    // Button stuff
    Rect test_button = draw_button(-0.5f, -0.5f, 1.0f, 0.5f, 1.0f, (Color){1.0f, 0.0f, 0.0f, 1.0f}, (Color){0.0f, 1.0f, 0.0f, 1.0f}, "Game Engine Button Test", (Color){1.0f, 1.0f, 1.0f, 1.0f});
    Rect quit_button = draw_button(-0.9f, -0.5f, 1.0f, 0.5f, 1.0f, (Color){0.8f, 0.3f, 0.4f, 1.0f}, (Color){0.0f, 0.0f, 0.0f, 1.0f}, "QUIT GAME", (Color){1.0f, 1.0f, 1.0f, 1.0f});
    if ((getMouseOver(&quit_button) && getMouseButtonDown(MOUSE_BUTTON_LEFT)) || getKeyDown(KEY_ESCAPE)) running = 0; 

    // Test logic
    if (getKeyDown(KEY_W)) printf("W was pressed\n");
    if (getMouseOver(&test_rect)) printf("Mouse is over the blue rect\n");
    if (getMouseOver(&test_button)) if (getMouseButtonDown(MOUSE_BUTTON_LEFT)) printf("Button Clicked\n");
    
    // if (isCollided(&test_rect, &test_button)) printf("Colliding!\n");

    // Clean up render
    destroy_shape((Shape*)&test_button);
    destroy_shape((Shape*)&quit_button);
}

void game_shutdown() {
    destroy_shape(&test_triangle);
}

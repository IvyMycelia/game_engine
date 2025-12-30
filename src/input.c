#include "input.h"

static unsigned char current_keys[GLFW_KEY_LAST + 1];
static unsigned char previous_keys[GLFW_KEY_LAST + 1];

static unsigned char current_mouse[8];
static unsigned char previous_mouse[8];

Vec2 mouse;

void input_update() {
    double mouse_x_pixels, mouse_y_pixels;
    glfwGetCursorPos(window, &mouse_x_pixels, &mouse_y_pixels);

    int width, height;
    glfwGetWindowSize(window, &width, &height);

    float scale_x = (float)fb_width / width;
    float scale_y = (float)fb_height / height;

    float mouse_x_fb = mouse_x_pixels * scale_x;
    float mouse_y_fb = mouse_y_pixels * scale_y;

    mouse.x = (float)(mouse_x_fb / fb_width) * 2.0f - 1.0f;
    mouse.y = 1.0f - (mouse_y_fb / fb_height) * 2.0f;


    for (int i = 0; i <= GLFW_KEY_LAST; i++) {
        previous_keys[i] = current_keys[i];
        current_keys[i] = glfwGetKey(window, i) == GLFW_PRESS;
    }

    for (int i = 0; i < 8; i++) {
        previous_mouse[i] = current_mouse[i];
        current_mouse[i] = glfwGetMouseButton(window, i) == GLFW_PRESS;
    }
}


// Keys
int getKey(int key) {
    return current_keys[key];
}

int getKeyDown(int key) {
    return current_keys[key] && !previous_keys[key];
}

int getKeyUp(int key) {
    return !current_keys[key] && previous_keys[key];
}


// Mouse
int getMouseOver(Shape* s) {
    switch (s->type) {
        case SHAPE_RECT:
            return  mouse.x >= s->rect.min.x &&
                    mouse.x <= s->rect.max.x &&
                    mouse.y >= s->rect.min.y &&
                    mouse.y <= s->rect.max.y;

        case SHAPE_CIRCLE:
            float dx = mouse.x - s->circle.center.x;
            float dy = mouse.y - s->circle.center.y;
            return (dx * dx + dy * dy) <= (s->circle.radius * s->circle.radius);

        case SHAPE_POLY:
        case SHAPE_TRIANGLE:
            return 0;
        
        case SHAPE_NONE:
        default: return 0;
    }
}

int getMouseButton(int button) {
    return current_mouse[button];
}

int getMouseButtonDown(int button) {
    return current_mouse[button] && !previous_mouse[button];
}

int getMouseButtonUp(int button) {
    return !current_mouse[button] && previous_mouse[button];
}
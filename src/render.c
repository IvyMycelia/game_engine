#include "render.h"

#include "GLFW/glfw3.h"
#include <GL/gl.h>

#include <stdio.h>

void render_init() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void render_clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void render_shutdown() {
    printf("Shutting down renderer...\n");
    // to be implemented
}
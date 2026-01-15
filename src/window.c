#include "window.h"
#include <GLFW/glfw3.h>

GLFWwindow* window;
static double last_time;

int fb_width, fb_height;

void window_init(int width, int height, const char* title) {
    if (!glfwInit()) {
        return;
    }

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    glfwMakeContextCurrent(window);

    glfwSwapInterval(0);
    last_time = glfwGetTime();

    glfwGetFramebufferSize(window, &fb_width, &fb_height);
    glViewport(0, 0, fb_width, fb_height);
}

double window_get_delta_time() {
    double current_time = glfwGetTime();
    float delta_time = (float)(current_time - last_time);
    last_time = current_time;
    return delta_time;
}

void window_poll_events() { glfwPollEvents(); }
void window_swap_buffers() { glfwSwapBuffers(window); }
int window_should_close() { return glfwWindowShouldClose(window); }

void window_shutdown() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

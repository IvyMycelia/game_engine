#ifndef WINDOW_H
#define WINDOW_H

#include "var.h"

void window_init(int width, int height, const char* title);
void window_shutdown();

int window_should_close();
void window_swap_buffers();
void window_poll_events();

double window_get_delta_time();

#endif // WINDOW_H
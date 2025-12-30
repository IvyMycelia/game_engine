#ifndef ENGINE_H
#define ENGINE_H

#include "var.h"

void engine_init(int width, int height, const char* title);
void engine_run();
void engine_shutdown();

#endif // ENGINE_H
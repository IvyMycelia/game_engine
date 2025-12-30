#ifndef GAME_H
#define GAME_H

#include "draw.h"
#include "text.h"
#include "input.h"
#include "collision.h"
#include "var.h"

void game_start();
void game_update(double delta_time);
void game_shutdown();

#endif // GAME_H
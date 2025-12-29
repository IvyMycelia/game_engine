#ifndef DRAW_H
#define DRAW_H

#include "var.h"

#include <GL/gl.h>

Polygon draw_rectangle(float x, float y, float width, float height, Color color, float border, Color border_color);
Polygon draw_triangle(float x1, float y1, float x2, float y2, float x3, float y3, Color fill, float border, Color border_color);
Polygon draw_button(float x, float y, float width, float height, float border, Color fill, Color border_color, const char* text, Color text_color);

#endif // DRAW_H
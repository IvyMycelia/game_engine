#ifndef DRAW_H
#define DRAW_H

#include "var.h"

#include <GL/gl.h>

Rect draw_rectangle(float x, float y, float width, float height, Color color);
void render_rectangle(const Rect* r, float border, Color border_color);
Triangle draw_triangle(Vec2 a, Vec2 b, Vec2 c, Color color);
void render_polygon(const Shape* s, float border, Color border_color);
Circle draw_circle(float cx, float cy, float radius, Color color);
void render_circle(const Circle* c, int segments, float border, Color border_color);
Rect draw_button(float x, float y, float width, float height, float border, Color fill, Color border_color, const char* text, Color text_color);
void destroy_shape(Shape* s);

#endif // DRAW_H
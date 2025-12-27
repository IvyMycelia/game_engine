#ifndef DRAW_H
#define DRAW_H

#include "var.h"

#include <GL/gl.h>

Rect draw_rectangle(Rect rect, Color color, float border, Color border_color);
Rect draw_button(Rect rect, float border, Color fill, Color border_color, const char* label, Color text_color);

#endif // DRAW_H
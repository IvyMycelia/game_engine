#ifndef TEXT_H
#define TEXT_H

#include "var.h"
#include "stb_image.h"

#include <GL/gl.h>

void load_font_texture(const char* path);
void draw_text(float x, float y, const char* text, Color color, float size);
void draw_char(char c, float x, float y, float size);

#endif // TEXT_H
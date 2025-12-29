#include "text.h"

#include <stdio.h>

GLuint FONT_TEXTURE;

void load_font_texture(const char* path) {
    int width, height, channels;
    unsigned char* data = stbi_load(path, &width, &height, &channels, 4);

    if (!data) {
        fprintf(stderr, "Failed to load font texture: %s\n", path);
        exit(1);
    }

    glGenTextures(1, &FONT_TEXTURE);
    glBindTexture(GL_TEXTURE_2D, FONT_TEXTURE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    stbi_image_free(data);
}

void draw_char(char c, float x, float y, float size) {
    const char font_chars[] =
        " !\"#$%&'()*+,-./"
        "0123456789:;<=>?"
        "@ABCDEFGHIJKLMNO"
        "PQRSTUVWXYZ[\\]^_"
        "`abcdefghijklmno"
        "pqrstuvwxyz{|}~";

    int index = -1;
    for (int i = 0; font_chars[i]; i++) {
        if (font_chars[i] == c) {
            index = i;
            break;
        }
    }
    if (index == -1) return;
    int cols = 16;
    int col = index % 16;
    int row = index / 16;

    float cell_w = 8.0f / 128.0f;
    float cell_h = 12.0f / 72.0f;

    float u0 = col * cell_w;
    float v0 = (5 - row) * cell_h;
    float u1 = u0 + cell_w;
    float v1 = v0 + cell_h;

    float ascent = size * 0.8f;
    float descent = size * 0.2f;

    glBindTexture(GL_TEXTURE_2D, FONT_TEXTURE);
    glBegin(GL_TRIANGLES);
    glTexCoord2f(u0, 1.0f - v1); glVertex2f(x, y + ascent);                 // Top-Left
    glTexCoord2f(u1, 1.0f - v1); glVertex2f(x + size, y + ascent);          // Top-Right
    glTexCoord2f(u1, 1.0f - v0); glVertex2f(x + size, y - descent);         // Bottom-Right
    
    glTexCoord2f(u0, 1.0f - v1); glVertex2f(x, y + ascent);                 // Top-Left
    glTexCoord2f(u1, 1.0f - v0); glVertex2f(x + size, y - descent);         // Bottom-Right
    glTexCoord2f(u0, 1.0f - v0); glVertex2f(x, y - descent);                // Bottom-Left
    glEnd();
}

void draw_text(float x, float y, const char* text, Color color, float size) {
    float start = x;
    glColor4f(color.r, color.g, color.b, color.a);
    glEnable(GL_TEXTURE_2D);
    for (int i = 0; text[i]; i++) {
        draw_char(text[i], start, y, size);
        start += size * (8.0f / 12.0f);
    }
    glDisable(GL_TEXTURE_2D);
}
#include "draw.h"
#include "text.h"

#include <stdio.h>
#include <string.h>


Polygon draw_rectangle(float x, float y, float width, float height, Color color, float border, Color border_color) {
    Polygon rect;
    rect.count = 4;
    rect.vertices = malloc(sizeof(Vec2) * 4);

    // Define Vertices
    rect.vertices[0] = (Vec2){x, y};                    // Bottom-left
    rect.vertices[1] = (Vec2){x + width, y};            // Bottom-right
    rect.vertices[2] = (Vec2){x + width, y + height};   // Top-right
    rect.vertices[3] = (Vec2){x, y + height};           // Top-left

    // Draw filled rectangle
    glColor4f(color.r, color.g, color.b, color.a);
    glBegin(GL_QUADS);
        for (int i = 0; i < 4; i++) glVertex2f(rect.vertices[i].x, rect.vertices[i].y);
    glEnd();

    // Draw border (when applicable)
    if (border > 0.0f) {
        glColor4f(border_color.r, border_color.g, border_color.b, border_color.a);
        glLineWidth(border);
        glBegin(GL_LINE_LOOP);
            for (int i = 0; i < 4; i++) glVertex2f(rect.vertices[i].x, rect.vertices[i].y);
        glEnd();
    }

    return rect;
}

Polygon draw_triangle(float x1, float y1, float x2, float y2, float x3, float y3, Color fill, float border, Color border_color) {
    Polygon tri;
    tri.count = 3;
    tri.vertices = malloc(sizeof(Vec2) * 3);

    // Define vertices
    tri.vertices[0] = (Vec2){x1, y1};
    tri.vertices[1] = (Vec2){x2, y2};
    tri.vertices[2] = (Vec2){x3, y3};

    // Draw filled triangle
    glColor4f(fill.r, fill.g, fill.b, fill.a);
    glBegin(GL_TRIANGLES);
        for (int i = 0; i < 3; i++) glVertex2f(tri.vertices[i].x, tri.vertices[i].y);
    glEnd();

    // Draw border (when applicable)
    if (border > 0) {
        glColor4f(border_color.r, border_color.g, border_color.b, border_color.a);
        glLineWidth(border);
        glBegin(GL_LINE_LOOP);
            for (int i = 0; i < 3; i++) glVertex2f(tri.vertices[i].x, tri.vertices[i].y);
        glEnd();
    }

    return tri;
}

Polygon draw_button(float x, float y, float width, float height, float border, Color fill, Color border_color, const char* text, Color text_color) {
    Polygon rect = draw_rectangle(x, y, width, height, fill, border, border_color);
    
    float glyph_aspect = 8.0f / 12.0f;
    float max_size_from_width = width / (strlen(text) * glyph_aspect);
    float size_from_height = height * 0.6f;

    float text_size = (max_size_from_width < size_from_height) ? max_size_from_width : size_from_height;

    draw_text(x + 0.05f, y + (height / 2) - (text_size / 2), text, text_color, text_size * 0.9f);

    return rect;
}
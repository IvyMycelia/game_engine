#include "draw.h"
#include "text.h"

#include <stdio.h>
#include <string.h>

/*
    Rectangles via triangles:

    x + width, y
    x, y + height
    x + width, y + height
    x, y
*/
Rect draw_rectangle(Rect rect, Color color, float border, Color border_color) {
    // Draw main rectangle
    glColor4f(color.r, color.g, color.b, color.a);
    glBegin(GL_QUADS);
        glVertex2f(rect.x, rect.y);                             // Bottom-left
        glVertex2f(rect.x + rect.width, rect.y);                // Bottom-right
        glVertex2f(rect.x + rect.width, rect.y + rect.height);  // Top-right
        glVertex2f(rect.x, rect.y + rect.height);               // Top-left
    glEnd();

    // Draw border (when applicable)
    if (border > 0.0f) {
        glColor4f(border_color.r, border_color.g, border_color.b, border_color.a);
        glLineWidth(border);
        glBegin(GL_LINE_LOOP);
            glVertex2f(rect.x, rect.y);
            glVertex2f(rect.x + rect.width, rect.y);
            glVertex2f(rect.x + rect.width, rect.y + rect.height);
            glVertex2f(rect.x, rect.y + rect.height);
        glEnd();
    }

    return rect;
}

Rect draw_button(Rect rect, float border, Color fill, Color border_color, const char* text, Color text_color) {
    // float padding = rect.height * 0.1f;
    draw_rectangle(rect, fill, border, border_color);
    
    float text_size = rect.height * 0.6f;
    float text_width = strlen(text) * text_size;
    float text_x = rect.x + (rect.width - text_width) / 2.0f;
    float text_y = rect.y + (rect.height - text_size) / 2.0f;
    draw_text(text_x, text_y, text, text_color, text_size);

    return rect;
}
#include "draw.h"
#include "text.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

const float PI = 3.14159265f;

Rect draw_rectangle(float x, float y, float width, float height, Color color) {
    Rect r = {0};
    r.type = SHAPE_RECT;
    r.color = color;

    r.rect.min = (Vec2){ x, y };
    r.rect.max = (Vec2){ x + width, y + height };

    return r;
}
void render_rectangle(const Rect* r, float border, Color border_color) {
    glColor4f(r->color.r, r->color.g, r->color.b, r->color.a);

    glBegin(GL_QUADS);
        glVertex2f(r->rect.min.x, r->rect.min.y);
        glVertex2f(r->rect.max.x, r->rect.min.y);
        glVertex2f(r->rect.max.x, r->rect.max.y);
        glVertex2f(r->rect.min.x, r->rect.max.y);
    glEnd();

    if (border > 0) {
        glColor4f(border_color.r, border_color.g, border_color.b, border_color.a);
        glLineWidth(border);
        glBegin(GL_LINE_LOOP);
            glVertex2f(r->rect.min.x, r->rect.min.y);
            glVertex2f(r->rect.max.x, r->rect.min.y);
            glVertex2f(r->rect.max.x, r->rect.max.y);
            glVertex2f(r->rect.min.x, r->rect.max.y);
        glEnd();
    }

}

Triangle draw_triangle(Vec2 a, Vec2 b, Vec2 c, Color color) {
    Triangle t = {0};
    t.type = SHAPE_TRIANGLE;
    t.color = color;

    t.poly.count = 3;
    t.poly.vertices = malloc(sizeof(Vec2) * 3);
    t.poly.vertices[0] = a;
    t.poly.vertices[1] = b;
    t.poly.vertices[2] = c;

    return t;
}
void render_polygon(const Shape* s, float border, Color border_color) {
    glColor4f(s->color.r, s->color.g, s->color.b, s->color.a);
    glBegin(GL_POLYGON);
        for (int i = 0; i < s->poly.count; i++) glVertex2f(s->poly.vertices[i].x, s->poly.vertices[i].y);
    glEnd();

    if (border > 0) {
        glColor4f(border_color.r, border_color.g, border_color.b, border_color.a);
        glLineWidth(border);
        glBegin(GL_LINE_LOOP);
            for (int i = 0; i < s->poly.count; i++) glVertex2f(s->poly.vertices[i].x, s->poly.vertices[i].y);
        glEnd();
    }
}

Circle draw_circle(float cx, float cy, float radius, Color color) {
    Circle c;
    c.type = SHAPE_CIRCLE;
    c.color = color;
    c.circle.center = (Vec2){cx, cy};
    c.circle.radius = radius;
    return c;
}
void render_circle(const Circle* c, int segments, float border, Color border_color) {
    glColor4f(c->color.r, c->color.g, c->color.b, c->color.a);

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(c->circle.center.x, c->circle.center.y);
        for (int i = 0; i <= segments; i++) {
            float theta = 2.0f * PI * i / segments;
            glVertex2f(
                c->circle.center.x + cosf(theta) * c->circle.radius,
                c->circle.center.y + sinf(theta) * c->circle.radius
            );
        }
    glEnd();
}

Rect draw_button(float x, float y, float width, float height, float border, Color fill, Color border_color, const char* text, Color text_color) {
    Shape s = {0};
    s.type = SHAPE_RECT;
    s.color = fill;

    s.rect.min = (Vec2){x, y};
    s.rect.max = (Vec2){x + width, y + height};
    
    render_rectangle((Rect*)&s, border, border_color);
    
    float glyph_aspect = 8.0f / 12.0f;
    float max_size_from_width = width / (strlen(text) * glyph_aspect);
    float size_from_height = height * 0.6f;

    float text_size = (max_size_from_width < size_from_height) ? max_size_from_width : size_from_height;

    draw_text(x + 0.05f, y + (height / 2) - (text_size / 2), text, text_color, text_size * 0.9f);

    return s;
}

void destroy_shape(Shape* s) {
    if (!s) return;

    if (s->type == SHAPE_POLY || s->type == SHAPE_TRIANGLE) {
        if (s->poly.vertices != NULL) free(s->poly.vertices);
        s->poly.vertices = NULL;
        s->poly.count = 0;
    }

    if (s->text) {
        free(s->text);
        s->text = NULL;
    }    

    s->type = SHAPE_NONE;
    s->color = (Color){0,0,0,0};
    s->textColor = (Color){0,0,0,0};
}
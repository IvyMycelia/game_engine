#include "collision.h"

#include <math.h>


int pointInRect(Vec2 p, RectData r) {
    return p.x >= r.min.x && p.x <= r.max.x &&
           p.y >= r.min.y && p.y <= r.max.y;
}

int pointInPoly(Vec2 p, Vec2* verts, int count) {
    int inside = 0;
    for (int i = 0, j = count - 1; i < count; j = i++)
        if (((verts[i].y > p.y) != (verts[j].y > p.y)) &&
             (p.x < (verts[j].x - verts[i].x) * (p.y - verts[i].y) / (verts[j].y - verts[i].y) + verts[i].x))
            inside = !inside;
    return inside;
}

int RectRectCollision(Rect* a, Rect* b) {
    return !(a->rect.max.x < b->rect.min.x ||
             a->rect.min.x > b->rect.max.x ||
             a->rect.max.y < b->rect.min.y ||
             a->rect.min.y > b->rect.max.y);
}

int RectCircleCollision(Rect* r, Circle* c) {
    float closestX = fmaxf(r->rect.min.x, fminf(c->circle.center.x, r->rect.max.x));
    float closestY = fmaxf(r->rect.min.y, fminf(c->circle.center.y, r->rect.max.y));

    float dx = c->circle.center.x - closestX;
    float dy = c->circle.center.y - closestY;

    return (dx * dx + dy * dy) <= (c->circle.radius * c->circle.radius);
}

int RectPolyCollision(Rect* r, Polygon* p) {
    Vec2 rectCorners[4] = {
        r->rect.min,
        {r->rect.max.x, r->rect.min.y},
        r->rect.max,
        {r->rect.min.x, r->rect.max.y}
    };
    for (int i = 0; i < 4; i++)
        if (pointInPoly(rectCorners[i], p->poly.vertices, p->poly.count))
            return 1;

    for (int i = 0; i < p->poly.count; i++)
        if (pointInRect(p->poly.vertices[i], r->rect))
            return 1;

    float minX = p->poly.vertices[0].x, maxX = p->poly.vertices[0].x;
    float minY = p->poly.vertices[0].y, maxY = p->poly.vertices[0].y;

    for (int i = 0; i < p->poly.count; i++) {
        if (p->poly.vertices[i].x < minX) minX = p->poly.vertices[i].x;
        if (p->poly.vertices[i].x > maxX) maxX = p->poly.vertices[i].x;
        if (p->poly.vertices[i].y < minY) minY = p->poly.vertices[i].y;
        if (p->poly.vertices[i].y > maxY) maxY = p->poly.vertices[i].y;
    }

    return !(r->rect.min.x > maxX || r->rect.max.x < minX ||
             r->rect.min.y > maxY || r->rect.max.y < minY);
}

int CircleCircleCollision(Circle* a, Circle* b) {
    float dx = a->circle.center.x - b->circle.center.x;
    float dy = b->circle.center.y - b->circle.center.y;
    float r = a->circle.radius + b->circle.radius;

    return (dx * dx + dy * dy) <= (r * r);
}

int CirclePolyCollision(Circle* c, Polygon* p) {
    float minX = p->poly.vertices[0].x, maxX = p->poly.vertices[0].x;
    float minY = p->poly.vertices[0].y, maxY = p->poly.vertices[0].y;

    for (int i = 0; i < p->poly.count; i++) {
        if (p->poly.vertices[i].x < minX) minX = p->poly.vertices[i].x;
        if (p->poly.vertices[i].x > maxX) maxX = p->poly.vertices[i].x;
        if (p->poly.vertices[i].y < minY) minY = p->poly.vertices[i].y;
        if (p->poly.vertices[i].y > maxY) maxY = p->poly.vertices[i].y;
    }

    float closestX = fmaxf(minX, fminf(c->circle.center.x, maxX));
    float closestY = fmaxf(minY, fminf(c->circle.center.y, maxY));

    float dx = c->circle.center.x - closestX;
    float dy = c->circle.center.y - closestY;

    return (dx * dx + dy * dy) <= (c->circle.radius * c->circle.radius);
}

int PolyPolyCollision(Polygon* a, Polygon* b) {
    float minAx = a->poly.vertices[0].x, maxAx = a->poly.vertices[0].x;
    float minAy = a->poly.vertices[0].y, maxAy = a->poly.vertices[0].y;

    for (int i = 0; i < a->poly.count; i++) {
        if (a->poly.vertices[i].x < minAx) minAx = a->poly.vertices[i].x;
        if (a->poly.vertices[i].x > maxAx) maxAx = a->poly.vertices[i].x;
        if (a->poly.vertices[i].y < minAy) minAy = a->poly.vertices[i].y;
        if (a->poly.vertices[i].y > maxAy) maxAy = a->poly.vertices[i].y;
    }

    float minBx = b->poly.vertices[0].x, maxBx = b->poly.vertices[0].x;
    float minBy = b->poly.vertices[0].y, maxBy = b->poly.vertices[0].y;

    for (int i = 0; i < b->poly.count; i++) {
        if (b->poly.vertices[i].x < minBx) minBx = b->poly.vertices[i].x;
        if (b->poly.vertices[i].x > maxBx) maxBx = b->poly.vertices[i].x;
        if (b->poly.vertices[i].y < minBy) minBy = b->poly.vertices[i].y;
        if (b->poly.vertices[i].y > maxBy) maxBy = b->poly.vertices[i].y;
    }

    return !(maxAx < minBx || minAx > minBx || maxAy < minBy || minAy > maxBy);
}


int isCollided(Shape* a, Shape* b) {
    switch (a->type) {
        case SHAPE_RECT:
            switch (b->type) {
                case SHAPE_RECT:        return RectRectCollision(a, b);
                case SHAPE_CIRCLE:      return RectCircleCollision(a, b);
                case SHAPE_POLY:
                case SHAPE_TRIANGLE:    return RectPolyCollision(a, b);
            } break;

        case SHAPE_CIRCLE:
            switch (b->type) {
                case SHAPE_RECT:        return RectCircleCollision(b, a);
                case SHAPE_CIRCLE:      return CircleCircleCollision(a, b);
                case SHAPE_POLY:
                case SHAPE_TRIANGLE:    return CirclePolyCollision(a, b);
            } break;
        
        case SHAPE_POLY:
        case SHAPE_TRIANGLE:
            switch (b->type) {
                case SHAPE_RECT:        return RectPolyCollision(b, a);
                case SHAPE_CIRCLE:      return CirclePolyCollision(b, a);
                case SHAPE_POLY:
                case SHAPE_TRIANGLE:    return PolyPolyCollision(a, b);
            } break;
    }
    return 0;
}
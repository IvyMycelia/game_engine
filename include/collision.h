#ifndef COLLISION_H
#define COLLISION_H

#include "var.h"

int pointInRect(Vec2 p, RectData r);
int pointInPoly(Vec2 p, Vec2* verts, int count);

int RectRectCollision(Rect* a, Rect* b);
int RectCircleCollision(Rect* r, Circle* c);
int RectPolyCollision(Rect* r, Polygon* p);
int CircleCircleCollision(Circle* a, Circle* b);
int CirclePolyCollision(Circle* c, Polygon* p);
int PolyPolyCollision(Polygon* a, Polygon* b);

int isCollided(Shape* a, Shape* b);

#endif // COLLISION_H
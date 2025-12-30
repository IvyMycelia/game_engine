#ifndef VAR_H
#define VAR_H

#include "GLFW/glfw3.h"
#include <GL/gl.h>
// #include <math.h>

extern GLuint FONT_TEXTURE;

extern const float PI;

typedef struct 
{
    unsigned char r; // Red component
    unsigned char g; // Green component
    unsigned char b; // Blue component
    unsigned char a; // Alpha component
} Color;

typedef struct 
{
    float x;    // X coordinate
    float y;    // Y coordinate
} Vec2;

typedef struct {
    Vec2* vertices;        // Max number of vertices
    int count;    // How many vertices
    Color color;
} Polygon;
typedef Polygon Rect;
typedef Polygon Triangle;
typedef Polygon Circle;

#endif // VAR_H
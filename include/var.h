#ifndef VAR_H
#define VAR_H

#include "GLFW/glfw3.h"
#include <GL/gl.h>

extern GLuint FONT_TEXTURE;

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
typedef Polygon Tri;


#endif // VAR_H
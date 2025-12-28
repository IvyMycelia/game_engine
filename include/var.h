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
    float x;    // Top-left corner x coordinate
    float y;    // Top-left corner y coordinate
    float width;    // Width of the rectangle
    float height;   // Height of the rectangle
    Color color;    // Color of the rectangle
} Rect;


#endif // VAR_H
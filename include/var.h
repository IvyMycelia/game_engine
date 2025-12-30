#ifndef VAR_H
#define VAR_H

#include "GLFW/glfw3.h"
#include <GL/gl.h>
// #include <math.h>

extern GLuint FONT_TEXTURE;
extern GLFWwindow* window;

extern int fb_width, fb_height;

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

typedef enum {
    SHAPE_NONE = 0,
    SHAPE_RECT,
    SHAPE_TRIANGLE,
    SHAPE_CIRCLE,
    SHAPE_POLY
} ShapeType;

typedef struct {
    Vec2 center;
    float radius;
} CircleData;

typedef struct {
    Vec2 min;
    Vec2 max;
} RectData;

typedef struct {
    ShapeType type;   // Type of shape

    union {
        struct {
            Vec2* vertices;   // Max number of vertices
            int count;        // How many vertices
        } poly;

        RectData rect;
        CircleData circle;
    };

    Color color;

    char* text;
    Color textColor;
} Shape;
typedef Shape Rect;
typedef Shape Circle;
typedef Shape Triangle;
typedef Shape Polygon;


#endif // VAR_H
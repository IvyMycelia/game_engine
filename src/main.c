#include "engine.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main() {
    engine_init(800, 600, "Game Engine");
    engine_run();
    engine_shutdown();
    
    return 0;
}
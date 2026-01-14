cmake_minimum_required(VERSION 3.20)
project(Engine C)

set(CMAKE_C_STANDARD 11)

# Include paths
include_directories("glfw3 CONFIG REQUIRED")
include_directories("include")

# Linker paths
set(SOURCES
    src/main.c
)
file(GLOB SOURCES "src/*c")

add_executable(Engine ${SOURCES})

set_target_properties(Engine PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin"
)

target_link_libraries(Engine
    glfw
    GL
    m
)

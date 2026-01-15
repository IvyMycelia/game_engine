cmake_minimum_required(VERSION 3.20)
project(Engine C)

set(CMAKE_C_STANDARD 11)

# === Sources ===
file(GLOB SOURCES "src/*.c")

add_executable(Engine ${SOURCES})

# === Include your own headers ===
target_include_directories(Engine PRIVATE "include")

# === Cross-platform GLFW + OpenGL setup ===
# Use find_package to locate GLFW installed via system package managers or vcpkg/brew
find_package(glfw3 REQUIRED)

target_link_libraries(Engine PRIVATE glfw)

# Detect OS for platform-specific libraries
if(WIN32)
    # Windows: OpenGL and win32 libraries
    target_link_libraries(Engine PRIVATE opengl32)
elseif(APPLE)
    # macOS: OpenGL framework
    find_library(COCOA_FRAMEWORK Cocoa REQUIRED)
    find_library(IOKIT_FRAMEWORK IOKit REQUIRED)
    find_library(COREVIDEO_FRAMEWORK CoreVideo REQUIRED)

    target_link_libraries(Engine PRIVATE
        "-framework OpenGL"
        ${COCOA_FRAMEWORK}
        ${IOKIT_FRAMEWORK}
        ${COREVIDEO_FRAMEWORK}
    )
elseif(UNIX)
    # Linux: OpenGL + math
    target_link_libraries(Engine PRIVATE GL m pthread X11 dl)
endif()

# === Output binary in ./bin ===
set_target_properties(Engine PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin"
)


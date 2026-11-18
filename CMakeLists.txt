cmake_minimum_required(VERSION 3.23)
project(camera_opengl)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(includes/glfw)
add_subdirectory(includes/glm)

add_executable(project
    src/main.cpp

    src/graphics/shaders.cpp
    src/graphics/camera.cpp

    src/objects/vertices.cpp
    src/objects/draw.cpp
    src/objects/textures.cpp

    src/math/mathgl.cpp

    src/stb_image.cpp
)

add_library(glad STATIC ${CMAKE_CURRENT_SOURCE_DIR}/includes/glad/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)

target_include_directories(project PRIVATE headers)

target_link_libraries(project PRIVATE glfw glm::glm glad)
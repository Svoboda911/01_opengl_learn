#pragma once

#include <iostream>
#include <vector>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class vertices {
public:
    unsigned int VBO, VAO;
    vertices(); // init vertices
    ~vertices(); // delete vertices
    void uploadWithTexture(std::vector<float>& vertices);
};

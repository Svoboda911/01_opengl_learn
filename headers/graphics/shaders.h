#pragma once
#include <fstream>
#include <iostream>
#include <sstream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class shaders {
public:    
    unsigned int id;
    shaders(const char* vertexShaderPath, const char* fragmentShaderPath);
    void use();
};

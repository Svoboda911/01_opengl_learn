#include "graphics/shaders.h"

shaders::shaders(const char* vertexShaderPath, const char* fragmentShaderPath) {
    // loading files 
    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;

    std::string vertexCode;
    std::string fragmentCode;

    vertexShaderFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    fragmentShaderFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    try {
        vertexShaderFile.open(vertexShaderPath);
        fragmentShaderFile.open(fragmentShaderPath);

        std::stringstream vertexBuffer, fragmentBuffer;

        vertexBuffer << vertexShaderFile.rdbuf();
        fragmentBuffer << fragmentShaderFile.rdbuf();

        vertexShaderFile.close();
        fragmentShaderFile.close();

        vertexCode = vertexBuffer.str();
        fragmentCode = fragmentBuffer.str();
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    const char* vertexSourceCode = vertexCode.c_str();
    const char* fragmentSourceCode = fragmentCode.c_str();

    if(!vertexSourceCode) std::cout << "failed to read source code (vertex)" << std::endl;
    if(!fragmentSourceCode) std::cout << "failed to read source code (frsagment)" << std::endl;

    // check 
    int succes;
    char infoLog[512];

    // init shaders
    unsigned int vertexShader, fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // source code
    glShaderSource(vertexShader, 1, &vertexSourceCode, NULL);
    glShaderSource(fragmentShader, 1, &fragmentSourceCode, NULL);

    // compile shader
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    // checking
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &succes);
    if(!succes) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << infoLog << std::endl;
    }
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &succes);
    if(!succes) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << infoLog << std::endl;
    }

    // init shader program
    id = glCreateProgram();
    
    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);
    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &succes);
    if(!succes) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::cout << infoLog << std::endl;
    }

    // delete shader
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void shaders::use() {
    glUseProgram(id);
}

/*
FOR SHADER:
    1) init (glCreateShader())
    2) source code (glShaderSource())
    3) compile (glCompileShader())
    4) check (succes and infolog)
    5) delete shader
FOR PROGRAM:
    1) init (glCreateProgram())
    2) append shaders (glAttachShader())
    3) link program (glLinkProgram())
    4) check
*/
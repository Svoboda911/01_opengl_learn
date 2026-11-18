#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "graphics/shaders.h"
#include "graphics/camera.h"

#include "objects/textures.h"
#include "objects/vertices.h"
#include "objects/draw.h"

#include "math/mathgl.h"
#include "globals.h"

int windowWidth = 512, windowHeight = 512;

camera cameraObject(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = (float)windowWidth / 2.0f;
float lastY = (float)windowHeight / 2.0f;
float lastTime = 0.0f, deltaTime = 0.0f;
bool firstMouse = true;

void framebuffer_size_callback(GLFWwindow* window, int w, int h);
void proccesInput(GLFWwindow* window, float deltaTime);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);

void program() {
    // init
    if(!glfwInit()) return;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(windowWidth, windowHeight, "project", NULL, NULL);
    if(!window) {glfwTerminate(); return;}

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return;

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouseCallback);
    glEnable(GL_DEPTH_TEST);

    // shader
    shaders shader("../shaders/vertex.glsl", "../shaders/fragment.glsl");

    // objects
    vertices cube;
    textureLoad("../textures/minecraft.jpg");
    auto cubeVertices = geometry::cube();
    cube.uploadWithTexture(cubeVertices);

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
    glm::mat4 view;

    // uniform location
    unsigned int modelUniformLocation = glGetUniformLocation(shader.id, "model");
    unsigned int viewUniformLocation = glGetUniformLocation(shader.id, "view");
    unsigned int projectionUniformLocation = glGetUniformLocation(shader.id, "projection");

    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.1, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        deltaTimeUpdate(lastTime, deltaTime);
        proccesInput(window, deltaTime);

        shader.use();
        view = cameraObject.getViewMatrix();

        // send value for uniforms
        glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewUniformLocation, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionUniformLocation, 1, GL_FALSE, glm::value_ptr(projection));

        // draw
        glBindVertexArray(cube.VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return;
}

int main() {
    program();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int w, int h) {
    windowWidth = w;
    windowHeight = h;
    glViewport(0, 0, w, h);
}
void proccesInput(GLFWwindow* window, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwDestroyWindow(window);
        glfwTerminate();
        return;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) cameraObject.move(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) cameraObject.move(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) cameraObject.move(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) cameraObject.move(RIGHT, deltaTime);
}
void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    if(firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    cameraObject.mouseMove(xoffset, yoffset);
}
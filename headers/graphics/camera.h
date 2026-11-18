#pragma once

#include <iostream>
#include "globals.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

enum cameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class camera {
private:
    void cameraUpdatePosition();
public:
    float cameraSpeed;
    float cameraYaw;
    float cameraPitch;
    float cameraSensitivity;
    float cameraZoom;

    glm::vec3 cameraPosition;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;

    camera(
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f)) :
        cameraPosition(position),
        cameraFront(0.0f, 0.0f, -1.0f),
        cameraUp(up),
        cameraSpeed(SPEED),
        cameraYaw(YAW),
        cameraPitch(PITCH),
        cameraSensitivity(SENSITIVITY),
        cameraZoom(ZOOM)
    {   
        cameraUpdatePosition();
    }
    
    void move(cameraMovement direction, float deltaTime);
    void mouseMove(float xoffset, float yoffset);

    glm::mat4 getViewMatrix();
};


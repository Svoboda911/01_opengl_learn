#include "graphics/camera.h"

void camera::move(cameraMovement direction, float deltaTime) {
    float velocity = SPEED * deltaTime;
    if (direction == FORWARD) {
        cameraPosition += velocity * cameraFront;
    }
    if (direction == BACKWARD) {
        cameraPosition -= velocity * cameraFront;
    }
    if (direction == LEFT) {
        cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * velocity;
    }
    if (direction == RIGHT) {
        cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * velocity;
    }
}

void camera::cameraUpdatePosition() {
    glm::vec3 direction;
    direction.x = glm::cos(glm::radians(cameraYaw)) * glm::cos(glm::radians(cameraPitch));
    direction.y = glm::sin(glm::radians(cameraPitch));
    direction.z = glm::sin(glm::radians(cameraYaw)) * glm::cos(glm::radians(cameraPitch));
    cameraFront = glm::normalize(direction);
}   

glm::mat4 camera::getViewMatrix() {
    return glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
}

void camera::mouseMove(float xoffset, float yoffset) {
    xoffset *= cameraSensitivity;
    yoffset *= cameraSensitivity;

    cameraYaw += xoffset;
    cameraPitch += yoffset;

    if(cameraPitch > 89.0f) cameraPitch = 89.0f;
    if(cameraPitch < -89.0f) cameraPitch = -89.0f;

    cameraUpdatePosition();
}   
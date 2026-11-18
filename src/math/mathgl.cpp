#include "math/mathgl.h"

void deltaTimeUpdate(float &lastTime, float &deltaTime) {
    float currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;
} 
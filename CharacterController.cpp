#include "CharacterController.h"

CharacterController::CharacterController(const std::string& texturePath, Shader& shader,
                                         int sheetCols, int sheetRows, int totalFrames, float frameTime)
    : Sprite(texturePath, shader, sheetCols, sheetRows, totalFrames, frameTime),
      x(500), y(100), speed(200.0f) {}

void CharacterController::Update(float deltaTime, GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        y += speed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        y -= speed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        x -= speed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        x += speed * deltaTime;

    Sprite::Update(deltaTime);
}

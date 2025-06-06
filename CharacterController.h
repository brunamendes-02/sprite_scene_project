#ifndef CHARACTER_CONTROLLER_H
#define CHARACTER_CONTROLLER_H

#include "sprite.h"
#include <GLFW/glfw3.h>

class CharacterController : public Sprite {
public:
    CharacterController(const std::string& texturePath, Shader& shader,
                        int sheetCols, int sheetRows, int totalFrames, float frameTime);

    void Update(float deltaTime, GLFWwindow* window);
    float x, y, speed;
};

#endif

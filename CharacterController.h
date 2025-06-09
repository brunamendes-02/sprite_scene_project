#ifndef CHARACTER_CONTROLLER_H
#define CHARACTER_CONTROLLER_H

#include "sprite.h"
#include <GLFW/glfw3.h>

class CharacterController : public Sprite {
public:
    float x, y;
    float speed;

    // 🔹 Construtor completo para animação (mantém se quiser usar animações no futuro)
    CharacterController(const std::string& texturePath, Shader& shader,
                        int sheetCols, int sheetRows, int totalFrames, float frameTime);

    // 🔸 Novo construtor para imagem estática (sem animação)
    CharacterController(const std::string& texturePath, Shader& shader);

    void Update(float deltaTime, GLFWwindow* window);
};

#endif

#ifndef SPRITE_H
#define SPRITE_H

#include <glad/gl.h>
#include <glm/glm.hpp>
#include "shader.h"
#include <string>

class Sprite {
public:
    Sprite(const std::string& texturePath, Shader& shader);
    void Draw(float x, float y, float width, float height);

private:
    GLuint VAO, VBO, texture;
    Shader& shader;
    void initRenderData();
    void loadTexture(const std::string& path);
};

#endif
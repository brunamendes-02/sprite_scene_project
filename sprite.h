#ifndef SPRITE_H
#define SPRITE_H

#include <glad/gl.h>
#include <glm/glm.hpp>
#include "shader.h"
#include <string>

class Sprite {
public:
    Sprite(const std::string& texturePath, Shader& shader,
           int sheetCols = 1, int sheetRows = 1, int totalFrames = 1, float frameTime = 0.1f);

    virtual void Update(float deltaTime);
    virtual void Draw(float x, float y, float width, float height);

protected:
    GLuint VAO, VBO, texture;
    Shader& shader;

    int sheetCols, sheetRows;
    int currentFrame, totalFrames;
    float frameTime, elapsedTime;

    void initRenderData();
    void loadTexture(const std::string& path);
};

#endif

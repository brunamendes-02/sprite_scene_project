#include "sprite.h"
#include <stb/stb_image.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Sprite::Sprite(const std::string& texturePath, Shader& shader, int sheetCols, int sheetRows, int totalFrames, float frameTime)
    : shader(shader), sheetCols(sheetCols), sheetRows(sheetRows),
      totalFrames(totalFrames), frameTime(frameTime),
      currentFrame(0), elapsedTime(0.0f) {
    loadTexture(texturePath);
    initRenderData();
}

void Sprite::Update(float deltaTime) {
    elapsedTime += deltaTime;
    if (elapsedTime >= frameTime) {
        currentFrame = (currentFrame + 1) % totalFrames;
        elapsedTime = 0.0f;
    }
}

void Sprite::Draw(float x, float y, float width, float height) {
    shader.use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(x, y, 0.0f));
    model = glm::scale(model, glm::vec3(width, height, 1.0f));
    shader.setMat4("model", model);

    // Calcula o UV do frame atual
    float col = currentFrame % sheetCols;
    float row = currentFrame / sheetCols;

    float u = col / float(sheetCols);
    float v = row / float(sheetRows);
    float uSize = 1.0f / float(sheetCols);
    float vSize = 1.0f / float(sheetRows);

    float vertices[] = {
        // pos       // tex
        0.0f, 1.0f, u, v + vSize,
        1.0f, 0.0f, u + uSize, v,
        0.0f, 0.0f, u, v,

        0.0f, 1.0f, u, v + vSize,
        1.0f, 1.0f, u + uSize, v + vSize,
        1.0f, 0.0f, u + uSize, v
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

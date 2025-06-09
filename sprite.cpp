#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include "sprite.h"
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

void Sprite::initRenderData() {
    float vertices[] = {
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Sprite::loadTexture(const std::string& path) {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);     
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);     

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // Inverte a textura no eixo Y
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 4);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cerr << "Erro ao carregar textura: " << path << std::endl;
    }

    stbi_image_free(data);
}

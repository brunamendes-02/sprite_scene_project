// main.cpp
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include <vector>
#include <iostream>

class Sprite {
public:
    GLuint VAO;
    GLuint textureID;
    glm::vec2 position;
    glm::vec2 scale;
    float rotation;
    Shader* shader;

    Sprite(GLuint vao, GLuint texID, Shader* shaderPtr)
        : VAO(vao), textureID(texID), shader(shaderPtr),
          position(0.0f), scale(1.0f), rotation(0.0f) {}

    void draw(const glm::mat4& projection) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(position, 0.0f));
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0, 0, 1));
        model = glm::scale(model, glm::vec3(scale, 1.0f));

        shader->use();
        shader->setMat4("model", model);
        shader->setMat4("projection", projection);

        glBindTexture(GL_TEXTURE_2D, textureID);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }
};

GLuint loadTexture(const char* path) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture: " << path << std::endl;
    }
    stbi_image_free(data);
    return textureID;
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Sprite Scene", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader shader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");

    float vertices[] = {
        // pos      // tex coords
        -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, 1.0f, 1.0f,

         0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 0.0f
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // ✅ Carregar texturas da pasta correta
    GLuint texTree = loadTexture("textures/tree.png");
    GLuint texDragon = loadTexture("textures/dragon.png");
    GLuint texChar = loadTexture("textures/character.png");
    GLuint texBg = loadTexture("textures/background.png");

    // ✅ Criar sprites
    Sprite background(VAO, texBg, &shader);
    background.position = glm::vec2(400, 300);  // Centro da tela
    background.scale = glm::vec2(800, 600);     // Preencher a tela

    Sprite tree(VAO, texTree, &shader);
    tree.position = glm::vec2(150, 100);
    tree.scale = glm::vec2(128, 128);

    Sprite dragon(VAO, texDragon, &shader);
    dragon.position = glm::vec2(600, 350);
    dragon.scale = glm::vec2(96, 96);

    Sprite character(VAO, texChar, &shader);
    character.position = glm::vec2(400, 200);
    character.scale = glm::vec2(64, 64);

    // ✅ Projeção ortográfica que mapeia 1 unidade = 1px
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Desenhar todos os sprites
        background.draw(projection);
        tree.draw(projection);
        dragon.draw(projection);
        character.draw(projection);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

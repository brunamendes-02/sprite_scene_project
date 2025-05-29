# Objetos Texturizados com OpenGL

Este é um projeto desenvolvido para a faculdade, com o objetivo de explorar conceitos de renderização 2D utilizando a biblioteca **OpenGL**. O programa renderiza objetos com texturas aplicadas, utilizando VAOs, VBOs e shaders personalizados.

## 📚 Descrição

O projeto demonstra o uso de sprites texturizados em uma cena 2D. Para isso, utilizamos a biblioteca **GLFW** para a criação da janela e controle de contexto OpenGL, e a biblioteca **GLAD** para o carregamento das funções OpenGL.

A renderização inclui:
- Carregamento e uso de shaders (vertex e fragment)
- Aplicação de texturas em sprites
- Gerenciamento de buffers (VAO/VBO)

---

## 🛠️ Tecnologias Utilizadas

- **C++**
- **OpenGL 4.6 (via GLAD)**
- **GLFW** – para criação de janelas e input
- **stb_image** – para carregamento de texturas
- **GLAD** – carregador de funções OpenGL
- **X11/Xrandr/Xi** – bibliotecas do sistema para interface gráfica (Linux)

---

## 🚀 Como compilar

Certifique-se de estar com as dependências instaladas (GLFW, OpenGL, etc). Em seguida, utilize o comando abaixo no terminal:

bash
g++ -Iinclude main.cpp sprite.cpp shader.cpp src/gl.c -o objetos-texturizados -I/usr/include -lglfw -ldl -lGL -lX11 -lpthread -lXrandr -lXi



## 🚀 Como rodar

Após a compilação bem-sucedida, execute o programa com o comando:

./objetos-texturizados

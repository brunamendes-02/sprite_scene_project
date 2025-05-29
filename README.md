# Textured Objects with OpenGL

This is a project developed for university purposes, aiming to explore 2D rendering concepts using the OpenGL library. The program renders objects with applied textures, utilizing VAOs, VBOs, and custom shaders.

## 📚 Description

The project demonstrates the use of textured sprites in a 2D scene. For this, we use the GLFW library to create the window and manage the OpenGL context, and the GLAD library to load OpenGL functions.

The rendering process includes:
- Loading and using shaders (vertex and fragment)
- Applying textures to sprites
- Managing buffers (VAO/VBO)

---

## 🛠️ Technologies Used

- **C++**
- **OpenGL 4.6 (via GLAD)**
- **GLFW**
- **stb_image**
- **GLAD**

---

## 🚀 How to Compile 
Make sure all dependencies are installed (GLFW, OpenGL, etc.). Then, run the following command in the terminal:

bash
g++ -Iinclude main.cpp sprite.cpp shader.cpp src/gl.c -o objetos-texturizados -I/usr/include -lglfw -ldl -lGL -lX11 -lpthread -lXrandr -lXi



## 🚀 How to Run
After a successful compilation, run the program with the command:

./objetos-texturizados

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include "textures.h"
#include "shader.h"

using std::cout;
using std::endl;
using std::uint8_t;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    glEnable(GL_DEBUG_OUTPUT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    Shader simpleShader1("shaders/texture_vertex.glsl", "shaders/texture_fragment.glsl");
    Shader simpleShader2("shaders/texture_vertex2.glsl", "shaders/texture_fragment2.glsl");

    float triangle_vertices[] = {
        -0.5f, -0.5f,  0.0f,    1.0f,  1.0f,  0.0f,   (-0.5f+1)/2,  (-0.5f+1)/2,
         0.5f, -0.5f,  0.0f,    0.0f,  1.0f,  0.0f,   (0.5f+1)/2,   (-0.5f+1)/2,
         0.0f,  0.5f,  0.0f,    0.0f,  0.0f,  1.0f,   (0.0f+1)/2,   (0.5f+1)/2
    }; 

    unsigned TRIANGLE_VBO, TRIANGLE_VAO;
    glGenVertexArrays(1, &TRIANGLE_VAO);
    glGenBuffers(1, &TRIANGLE_VBO);

    glBindVertexArray(TRIANGLE_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, TRIANGLE_VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    float square_vertices[] = {
        -0.9f, -0.9f,  0.0f,   1.0f,  0.0f,  0.0f,  0.0f,  1.0f, // ↙
         0.0f, -0.9f,  0.0f,   0.0f,  1.0f,  0.0f,  1.0f,  1.0f, // ➘
        -0.9f,  0.3f,  0.0f,   0.0f,  0.0f,  1.0f,  0.0f,  0.0f, // ↖ 
         0.0f,  0.3f,  0.0f,   1.0f,  0.0f,  1.0f,  1.0f,  0.0f, // ➚
    };
    unsigned square_indices[] = {
        0, 1, 2,
        1, 2, 3,
    };

    unsigned SQUARE_VBO, SQUARE_EBO, SQUARE_VAO; 
    glGenVertexArrays(1, &SQUARE_VAO);
    glGenBuffers(1, &SQUARE_VBO);
    glGenBuffers(1, &SQUARE_EBO);

    glBindVertexArray(SQUARE_VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, SQUARE_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(square_vertices), square_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SQUARE_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(square_indices), square_indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GL_FLOAT), (void*)(sizeof(float)*0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GL_FLOAT), (void*)(sizeof(float)*3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GL_FLOAT), (void*)(sizeof(float)*6));
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    Textures::registerNewTexture("resources/paving_stones/PavingStones41_col.jpg", "stones");
    Textures::registerNewTexture("resources/rocks/Rocks19_col.jpg", "rocks");
    Textures::registerNewTexture("resources/thinking_face.png", "tf");

    simpleShader2.use();
    simpleShader2.setInt("texture1", 0);
    simpleShader2.setInt("texture2", 1);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Textures::bindTexture("stones", 0);
        Textures::bindTexture("tf", 1);

        simpleShader1.use();
        glBindVertexArray(TRIANGLE_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        simpleShader2.use();
        float timeValue = glfwGetTime();
        simpleShader2.setFloat("time", timeValue);
        glBindVertexArray(SQUARE_VAO);
        glDrawElements(GL_TRIANGLES, 3*2, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &TRIANGLE_VAO);
    glDeleteBuffers(1, &TRIANGLE_VBO);

    glDeleteVertexArrays(1, &SQUARE_VAO);
    glDeleteBuffers(1, &SQUARE_VBO);
    glDeleteBuffers(1, &SQUARE_EBO);

    glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

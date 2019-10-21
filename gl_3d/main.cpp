#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "file.h"

#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using std::cout;
using std::endl;
using std::uint8_t;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window);
int createProgram(std::string vertexShaderFile, std::string fragmentShaderFile);

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

    int simpleShaderProgram1 = createProgram("shaders/simple_vertex.glsl", "shaders/simple_fragment.glsl");
    int simpleShaderProgram2 = createProgram("shaders/simple_vertex.glsl", "shaders/simple_fragment2.glsl");

    float triangle_vertices[] = {
        -0.5f, -0.5f, 0.0f, 
         0.5f, -0.5f, 0.0f, 
         0.0f,  0.5f, 0.0f,
    }; 

    unsigned TRIANGLE_VBO, TRIANGLE_VAO;
    glGenVertexArrays(1, &TRIANGLE_VAO);
    glGenBuffers(1, &TRIANGLE_VBO);

    glBindVertexArray(TRIANGLE_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, TRIANGLE_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    
    float square_vertices[] = {
        -0.9f, -0.9f,  0.0f, // ↙
         0.0f, -0.9f,  0.0f, // ➘
        -0.9f,  0.3f,  0.0f, // ↖ 
         0.0f,  0.3f,  0.0f, // ➚
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(simpleShaderProgram1);
        glBindVertexArray(TRIANGLE_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(simpleShaderProgram2);

        // update shader uniform
        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        float redValue = sin(timeValue + 2*M_PI/3) / 2.0f + 0.5f;
        float blueValue = sin(timeValue + 4*M_PI/3) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(simpleShaderProgram2, "ourColor");
        glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f);
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

int createProgram(std::string vertexShaderFile, std::string fragmentShaderFile)
{
    std::string vertexShaderString = File::Read(vertexShaderFile);
    char* vertexShaderSource = (char*)vertexShaderString.c_str();

    int success;
    char infoLog[512];

    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << endl << infoLog << endl;
    }

    std::string fragmentShaderString = File::Read(fragmentShaderFile);
    char* fragmentShaderSource = (char*)fragmentShaderString.c_str();

    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << endl << infoLog << endl;
    }

    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS,  &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << endl << infoLog << endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    return shaderProgram;
}

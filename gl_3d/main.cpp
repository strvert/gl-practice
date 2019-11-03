#include <glad/glad.h>
// ↑ Must be included first
#include <GLFW/glfw3.h>

#include <cmath>
#include <cstdint>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "shader.h"
#include "stb_image.h"
#include "textures.h"

using std::cout;
using std::endl;
using std::uint8_t;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL",
                                          nullptr, nullptr);
    if (window == nullptr) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    glEnable(GL_DEBUG_OUTPUT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    float plane_vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  //
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,   //
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,    //
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,   //
                                          //
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,   //
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,    //
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,     //
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,    //
                                          //
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,    //
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   //
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  //
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,   //
                                          //
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,     //
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,    //
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,   //
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,    //
                                          //
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  //
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,   //
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,    //
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,   //
                                          //
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,   //
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,    //
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,     //
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,    //
    };

    unsigned plane_indices[] = {
        0,  1,  2,  0,  2,  3,   //
        4,  5,  6,  4,  6,  7,   //
        8,  9,  10, 8,  10, 11,  //
        12, 13, 14, 12, 14, 15,  //
        16, 17, 18, 16, 18, 19,  //
        20, 21, 22, 20, 22, 23,  //
        24, 25, 26, 24, 26, 27,  //
        28, 29, 30, 28, 30, 31,  //
        32, 33, 34, 33, 34, 35,  //
    };

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

    unsigned plane_ebo, plane_vbo, plane_vao;

    glGenVertexArrays(1, &plane_vao);
    glGenBuffers(1, &plane_ebo);
    glGenBuffers(1, &plane_vbo);

    glBindVertexArray(plane_vao);

    glBindBuffer(GL_ARRAY_BUFFER, plane_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(plane_vertices), plane_vertices,
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, plane_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(plane_indices), plane_indices,
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT),
                          reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT),
                          reinterpret_cast<void*>(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    Textures::New("resources/redbricks/redbricks2b-albedo.png", "red_brick");
    Shader shader1("shaders/transform_vertex.glsl",
                   "shaders/texture_fragment.glsl");

    shader1.use();
    shader1.setInt("texture1", 0);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Textures::bind("red_brick", 0);
        shader1.use();

        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        projection = glm::perspective(
            glm::radians(45.0f), float(SCR_WIDTH / SCR_HEIGHT), 0.1f, 100.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        shader1.setMat4("view", view);
        shader1.setMat4("projection", projection);

        glBindVertexArray(plane_vao);
        for (int i = 0; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            glm::vec3& elm = cubePositions[i];
            model = glm::translate(model, elm);
            model = glm::rotate(
                model, (i * 20) + (float)glfwGetTime() * glm::radians(45.0f),
                glm::vec3(0.5f, 1.0f, 0.0f));
            shader1.setMat4("model", model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &plane_vao);
    glDeleteBuffers(1, &plane_vbo);
    glDeleteBuffers(1, &plane_ebo);

    glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}


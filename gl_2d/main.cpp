#include "game.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "texture.h"
#include "sprite.h"
#include "resource_manager.h"

void key_callback(GLFWwindow* window, int key, int code, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    // if (key >= 0 && key < 1024)
    // {
    //     if (action == GLFW_PRESS)
    //         Breakout.Keys[key] = GL_TRUE;
    //     else if (action == GLFW_RELEASE)
    //         Breakout.Keys[key] = GL_FALSE;
    // }
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    GLFWwindow* window = glfwCreateWindow(1280, 720, "gl_game", nullptr, nullptr);
    glViewport(0, 0, 1280, 720);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();
    glGetError();

    glfwSetKeyCallback(window, key_callback);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);

    Texture2D arch = ResourceManager::LoadTexture2D("resources/images/archlinux.png", "archlinux");
    Shader simple = ResourceManager::LoadShaderVF("resources/shaders/simpleVertex.glsl", "resources/shaders/simpleFragment.glsl", "simple");

    // simple.Use();
    // simple.SetInteger("image", 0);
    // glm::mat4 projection = glm::ortho(0.0f, 200.0f, 200.0f, 0.0f, -1.0f, 1.0f);
    // simple.SetMatrix4("projection", projection);
    
    Sprite sprite(simple);

    do {
        glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        sprite.Draw(arch, glm::vec2(200, 200));

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    while (!glfwWindowShouldClose(window));
}

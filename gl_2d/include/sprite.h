#ifndef __GL_GAME_SPRITE_H
#define __GL_GAME_SPRITE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "texture.h"
#include "shader.h"

class Sprite
{
public:
    Sprite(Shader& shader);
    ~Sprite();

    void Draw(Texture2D& texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

private:
    Shader shader;
    GLuint quadVAO;

    void initRenderData();
};

#endif // __GL_GAME_SPRITE_H

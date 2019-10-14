#ifndef __GL_GAME_SHADER_H
#define __GL_GAME_SHADER_H

#include <string>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shader
{
private:
    void checkCompileErrors(GLuint object, std::string type);

public:
    GLuint ID;
    Shader() {}
    Shader &Use();

    void Compile(const GLchar *vertexSource, const GLchar *fragmentSource, const GLchar *geometrySource = nullptr);

    void SetFloat(const GLchar *name, GLfloat value, GLboolean useShader = false);
    void SetInteger(const GLchar *name, GLint value, GLboolean useShader = false);
    void SetMatrix4(const GLchar *name, glm::mat4& matrix, GLboolean useShader = false);
    void SetVector3(const GLchar *name, glm::vec3& value, GLboolean useShader = false);
};

#endif // __GL_GAME_SHADER_H


#ifndef __GL_3D_SHADER_H 
#define __GL_3D_SHADER_H

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    unsigned int Id;

    Shader(const std::string& vertexPath, const std::string& fragmentPath);

    void use();

    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setFloat4(const std::string& name, float value1, float value2, float value3, float value4) const;
    void setMat4(const std::string& name, glm::mat4 mat) const;
};

#endif // __GL_3D_SHADER_H

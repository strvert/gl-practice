#ifndef __GL_GAME_RESOURCE_MANAGER_H
#define __GL_GAME_RESOURCE_MANAGER_H

#include <string>
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "texture.h"

class ResourceManager
{
public:
    inline static std::map<std::string, Shader> Shaders;
    inline static std::map<std::string, Texture2D> Textures;

    static Shader LoadShaderVF(const std::string& vShaderPath, const std::string& fShaderPath, const std::string& name);
    static Shader LoadShaderVFG(const std::string& vShaderPath, const std::string& fShaderPath, const std::string& gShaderPath, const std::string& name);
    static Shader GetShader(const std::string& name);

    static Texture2D LoadTexture2D(const std::string& imagePath, const std::string& imageName);
    static Texture2D GetTexture2D(const std::string& imageName);

    static void ClearAll();

private:
    ResourceManager(){}

    static Shader loadShaderFromFile(const std::string& vShaderPath, const std::string& fShaderPath, const std::string& gShaderPath = "");
    static Texture2D loadTexture2DFromFile(const std::string& filepath);
};


#endif // __GL_GAME_RESOURCE_MANAGER_H


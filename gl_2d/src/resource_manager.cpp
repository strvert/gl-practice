#include "resource_manager.h"
#include <string>
#include <vector>

#include "lodepng.h"
#include "shader.h"
#include "file.h"
#include "texture.h"

Shader ResourceManager::LoadShaderVF(const std::string& vShaderPath, const std::string& fShaderPath, const std::string& name)
{
    Shaders[name] = loadShaderFromFile(vShaderPath, fShaderPath, "");
    return Shaders[name];
}

Shader ResourceManager::LoadShaderVFG(const std::string& vShaderPath, const std::string& fShaderPath, const std::string& gShaderPath, const std::string& name)
{
    Shaders[name] = loadShaderFromFile(vShaderPath, fShaderPath, gShaderPath);
    return Shaders[name];
}

Shader ResourceManager::GetShader(const std::string& name)
{
    return Shaders[name];
}

Texture2D ResourceManager::LoadTexture2D(const std::string& imagePath, const std::string& name)
{
    Textures[name] = loadTexture2DFromFile(imagePath);
    return Textures[name];
}

Texture2D ResourceManager::GetTexture2D(const std::string& name)
{
    return Textures[name];
}

Shader ResourceManager::loadShaderFromFile(const std::string& vShaderPath, const std::string& fShaderPath, const std::string& gShaderPath)
{
    File vf(vShaderPath);    
    std::vector<std::uint8_t> vShaderData = vf.Read();
    std::string vShaderCode(vShaderData.begin(), vShaderData.end());
    std::cout << vShaderCode << std::endl;

    File ff(fShaderPath);    
    std::vector<std::uint8_t> fShaderData = ff.Read();
    std::string fShaderCode(fShaderData.begin(), fShaderData.end());
    std::cout << fShaderCode << std::endl;

    std::vector<std::uint8_t> gShaderData;
    if (!gShaderPath.empty())
    {
        File gf(gShaderPath);    
        gShaderData = gf.Read();
    }
    std::string gShaderCode(gShaderData.begin(), gShaderData.end());
        
    Shader shader;
    shader.Compile(vShaderCode.c_str(), fShaderCode.c_str(), gShaderCode.empty() ? nullptr : gShaderCode.c_str());
    return shader;
}

Texture2D ResourceManager::loadTexture2DFromFile(const std::string& filepath)
{
    std::vector<std::uint8_t> image;
    unsigned int width, height;

    File f(filepath);    
    switch (f.Type())
    {
        case FileTypes::PNG:
            lodepng::decode(image, width, height, f.Read());
            break;

        case FileTypes::JPG:
            break;

        case FileTypes::BMP:
            break;

        case FileTypes::TIFF:
            break;

        default:
            break;
    }

    return Texture2D(width, height, image.data());
}

void ResourceManager::ClearAll()
{
    for (auto& shader: Shaders)
    {
        glDeleteProgram(shader.second.ID);
    } 
    for (auto& texture: Textures)
    {
        glDeleteTextures(1, &texture.second.ID);
    } 
}

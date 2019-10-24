#ifndef __GL_3D_TEXTURES_H
#define __GL_3D_TEXTURES_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <iostream>
#include <map>
#include <string>

class Textures
{
private:
    static inline std::map<std::string, unsigned> texture_ids;
public:
    static void registerNewTexture(std::string path, std::string texture_name);
    static unsigned getTextureId(std::string texture_name);
    static void bindTexture(std::string texture_name, int unit);
};

#endif // __GL_3D_TEXTURES_H

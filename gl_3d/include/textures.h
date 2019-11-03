#ifndef __GL_3D_TEXTURES_H
#define __GL_3D_TEXTURES_H

#include <glad/glad.h>

#include <iostream>
#include <map>
#include <string>

#include "stb_image.h"

class Textures {
private:
    static inline std::map<std::string, unsigned> texture_ids;

public:
    static void New(std::string path, std::string texture_name);
    static unsigned getId(std::string texture_name);
    static void bind(std::string texture_name, int unit);
};

#endif  // __GL_3D_TEXTURES_H

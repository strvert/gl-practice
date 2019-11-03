#include "textures.h"

void Textures::New(std::string path, std::string texture_name) {
    unsigned texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, ch;
    uint8_t* data = stbi_load(path.c_str(), &width, &height, &ch, 0);

    if (data) {
        unsigned format;
        switch (ch) {
            case 3:
                format = GL_RGB;
                break;
            case 4:
                format = GL_RGBA;
                break;
            default:
                format = GL_RGB;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture. (" << texture_name << ")"
                  << std::endl;
    }
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    texture_ids[texture_name] = texture;
}

unsigned Textures::getId(std::string texture_name) {
    return texture_ids.at(texture_name);
}

void Textures::bind(std::string texture_name, int unit) {
    glActiveTexture(int(GL_TEXTURE0 + unit));
    glBindTexture(GL_TEXTURE_2D, texture_ids.at(texture_name));
}

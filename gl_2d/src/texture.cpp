#include <string>
#include <vector>
#include "texture.h"
#include "file.h"

#include "lodepng.h"
#include <jpeglib.h>

Texture2D::Texture2D()
    :Width(0), Height(0),
    Internal_Format(GL_RGBA), Image_Format(GL_RGBA),
    Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT),
    Filter_Min(GL_LINEAR), Filter_Max(GL_LINEAR)
{
    glGenTextures(1, &this->ID);
}

Texture2D::Texture2D(GLuint width, GLuint height, std::uint8_t* data)
{
    glGenTextures(1, &this->ID);
    this->Generate(width, height, data);
}

void Texture2D::Generate(GLuint width, GLuint height, std::uint8_t* data)
{
    this->Width = width;
    this->Height = height;

    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, this->Width, this->Height, 0, this->Image_Format, GL_UNSIGNED_BYTE, data);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->ID);
}

#ifndef __GL_GAME_TEXTURE_H
#define __GL_GAME_TEXTURE_H

#include <GL/glew.h>
#include <string>
#include <cstdint>

class Texture2D
{
public:
    GLuint ID;
    GLuint Width, Height;
    GLuint Internal_Format;
    GLuint Image_Format; 

    GLuint Wrap_S; 
    GLuint Wrap_T; 
    GLuint Filter_Min;
    GLuint Filter_Max;

    Texture2D();
    Texture2D(GLuint width, GLuint height, std::uint8_t* data);
    void Generate(GLuint width, GLuint height, std::uint8_t* data);
    void Bind() const;
};

#endif // __GL_GAME_TEXTURE_H

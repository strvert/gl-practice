#version 410 core

in vec2 TexCoord;
uniform sampler2D texture_col;

out vec4 FragColor;

void main()
{
    FragColor = texture(texture_col, TexCoord);
}

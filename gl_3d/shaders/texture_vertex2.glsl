#version 410 core

layout (location = 0) in vec3 vertices;
layout (location = 1) in vec3 colors;
layout (location = 2) in vec2 texture_uv;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(vertices, 1);
    ourColor = colors;
    TexCoord = texture_uv;
}

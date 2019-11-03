#version 410 core

layout (location = 0) in vec3 vertices;
layout (location = 1) in vec2 texture_uv;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(vertices, 1);
    TexCoord = texture_uv;
}

#version 410 core

layout(location = 0) in vec3 vertices;
layout(location = 1) in vec3 vertexColors;

out vec3 colors;

void main()
{
    colors = vertexColors;
    gl_Position = vec4(vertices, 1.0f);
}

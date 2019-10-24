#version 410 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float time;

vec2 rotate2D(vec2 point, float angle, vec2 med)
{
    point -= med;
    point = vec2(
        point.x*cos(angle) - point.y*sin(angle),
        point.x*sin(angle) + point.y*cos(angle)
    );
    return point - med;
}

void main()
{
    vec4 t1 = texture(texture1, TexCoord);
    vec4 t2 = texture(texture2, rotate2D(TexCoord, mod(time, 2*3.1415926), vec2(0.5f, 0.5f)));
    FragColor = (t1 * (1-t2.a)) + mix((t1 * (t2.a)), t2*t2.a, sin(time*10.0f)*0.5f+0.5f);
}

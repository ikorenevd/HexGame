#version 330 core

layout (location = 0) in vec2 in_pos;
layout (location = 1) in vec2 in_uv;
layout (location = 2) in vec4 in_color;

out vec4 color;
out vec2 uv;

void main()
{
    gl_Position = vec4(in_pos, 0.0, 1.0);
    color = in_color;
    uv = in_uv;
};
#version 330 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 texCoord;

uniform mat4 transform;
uniform mat4 view;

out vec2 TexCoord;

void main()
{
	gl_Position = view * transform * vec4(pos, 0.0, 1.0);
	TexCoord = texCoord;
};
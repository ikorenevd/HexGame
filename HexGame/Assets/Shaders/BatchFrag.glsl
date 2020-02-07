#version 330 core

in vec4 color;
in vec2 uv;

uniform sampler2D u_texture;

void main()
{
	gl_FragColor = texture(u_texture, uv) * color;
};

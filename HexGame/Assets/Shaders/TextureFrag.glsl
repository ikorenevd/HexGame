#version 330 core

in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform float opacity;

void main()
{
	vec4 texture = texture(ourTexture, TexCoord);
	gl_FragColor = vec4(texture.rgb, texture.a * opacity);
};
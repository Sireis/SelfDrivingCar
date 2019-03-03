#version 330 core

in vec4 color;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D Tex;

void main()
{
	FragColor = texture(Tex, TexCoord);
}
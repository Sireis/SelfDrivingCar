#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 rgba;
layout (location = 2) in vec2 aTexCoord;

out vec4 color;
out vec2 TexCoord;

uniform mat4 transform;
uniform float aspect_ratio;

void main() 
{
	gl_Position = vec4(aspect_ratio * aPos.x, aPos.y, aPos.z, 1.0);
	color = rgba;
	TexCoord = aTexCoord;
}
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 colour;
layout (location  = 2) in vec2 texCoord;

uniform mat4 T_MVP;

out DATA
{
	vec4 colour;
} vs_out;

void main()
{
	gl_Position = T_MVP * vec4(position, 1.0);
	vs_out.colour = colour;
}
#version 330 core
layout (location = 0) in vec3 position;
layout (location  = 1) in vec2 texCoord;
layout (location  = 2) in vec3 normal;
layout (location  = 3) in vec3 tangent;

out vec2 texCoord0;
out vec3 positions0;

uniform mat4 T_MVP;


out DATA
{
	vec4 position;
	vec4 color;
} vs_out;

void main()
{
	gl_Position = T_MVP * vec4(position, 1.0);
	texCoord0 = texCoord;
	positions0 = position;
	vs_out.position = ml_matrix * vec4(position, 1.0);
	vs_out.color = color;
}
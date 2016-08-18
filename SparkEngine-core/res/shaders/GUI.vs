#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 colour;
layout (location  = 2) in vec2 texCoord;
layout (location  = 3) in int texID;

uniform mat4 T_MVP;


out DATA
{
	vec2 uv;
	float tid;
	vec4 color;
} vs_out;

void main()
{
	gl_Position = T_MVP *  vec4(position, 1.0);
	vs_out.uv = texCoord;
	vs_out.tid = texID;
	vs_out.color = colour;
}
#version 330 core
layout (location = 0) out vec4 fragColor;

in vec2 texCoord0;
in vec3 positions0;

in DATA
{
	vec4 colour;
} fs_in;

void main()
{
	fragColor = fs_in.colour;
}
#version 330 core
layout (location = 0) out vec4 fragColor;

in vec2 texCoord0;
in vec3 positions0;

uniform vec3 R_ambient;
uniform sampler2D diffuse;

void main()
{

	fragColor = texture(diffuse,texCoord0) * vec4(R_ambient, 1);
}
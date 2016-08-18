#version 330 core
layout (location = 0) out vec4 fragColor;

uniform sampler2D textures[32];

in DATA
{
	vec2 uv;
	float tid;
	vec4 color;
} fs_in;

void main()
{
	vec4 colour = fs_in.color;
	if (fs_in.tid > 0)
	{
		int a = int(fs_in.tid - 1);
		colour = texture(textures[a], fs_in.uv);
	}
	fragColor = colour;
}
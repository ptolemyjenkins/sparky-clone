#version 330 core
layout (location = 0) out vec4 fragColor;

uniform vec4 col = vec4( 1.0 , 0.2 , 1.0 , 1.0 );
uniform vec2 light_pos;

in vec4 pos;
void main()
{
	float intensity = 1.0 /length(pos.xy - light_pos);
	fragColor = col * intensity;
}
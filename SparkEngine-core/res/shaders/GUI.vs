#version 330

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoord;
out vec2 texCoord0;

uniform mat4 T_transform;

void main(){
	texCoord0 = texCoord;
	gl_Position = T_transform * vec4(position,1.0,1.0);
}
#version 330

in vec2 texCoord0;
out vec4 fragColor;

uniform sampler2D R_GUI;

void main(){
	fragColor = texture(R_GUI,texCoord0.xy);
}
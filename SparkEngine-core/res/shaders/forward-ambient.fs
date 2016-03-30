#version 330
#include "sampling.glh"

in vec2 texCoord0;
in vec3 worldPos0;
in mat3 tbnMatrix;
out vec4 fragColor;

uniform vec3 R_ambient;
uniform vec3 C_eyePos;
uniform sampler2D diffuse;
uniform sampler2D dispMap;

uniform float dispMapScale;
uniform float dispMapBias;

void main(){
	vec3 directionToEye = normalize(C_eyePos - worldPos0);
	vec2 texCoords = calcParallaxTexCoords(dispMap, tbnMatrix, directionToEye, texCoord0, dispMapScale, dispMapBias);
	fragColor = texture(diffuse,texCoords) * vec4(R_ambient, 1);
}

#version 330
#include "lighting.fsh"

uniform SpotLight R_spot;

vec4 calcLightingEffect(vec3 normal, vec3 worldPos){
	return calcSpotLight(R_spot, normalize(normal), worldPos);
}

#include "lightingMain.fsh"

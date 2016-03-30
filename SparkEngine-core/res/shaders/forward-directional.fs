#version 330
#include "lighting.fsh"

uniform DirectionalLight R_directional;

vec4 calcLightingEffect(vec3 normal, vec3 worldPos){
	return calcDirectionalLight(R_directional, normalize(normal), worldPos);
}

#include "lightingMain.fsh"

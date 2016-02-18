#version 330
#include "lighting.fsh"

uniform PointLight R_point;

vec4 calcLightingEffect(vec3 normal, vec3 worldPos){
	return calcPointLight(R_point, normalize(normal), worldPos);
}

#include "lightingMain.fsh"
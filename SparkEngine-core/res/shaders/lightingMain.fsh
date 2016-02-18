#include "sampling.glh"
void main(){
	vec3 directionToEye  = normalize(C_eyePos - worldPos0);
	vec2 texCoords = calcParallaxTexCoords(dispMap, tbnMatrix, directionToEye, texCoord0, dispMapScale, dispMapBias);
	vec3 normal = normalize(tbnMatrix1 * (255.0/128.0 * texture(normalMap, texCoords).xyz - 1));
	fragColor = texture(diffuse, texCoords) * calcLightingEffect(normal, worldPos0);
}
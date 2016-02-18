in vec2 texCoord0;
in vec3 worldPos0;
in mat3 tbnMatrix;
in mat3 tbnMatrix1;
out vec4 fragColor;
in vec3 normal0;

uniform sampler2D diffuse;
uniform sampler2D normalMap;
uniform sampler2D dispMap;

uniform float dispMapScale;
uniform float dispMapBias;

#include "lighting.glh"
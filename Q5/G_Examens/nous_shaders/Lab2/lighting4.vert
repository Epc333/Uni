#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;
out vec3 N, V, L;

uniform mat4 modelViewProjectionMatrix, modelViewMatrix;
uniform mat3 normalMatrix;
uniform vec3 lightPosition;

void main()
{
	vec3 P = (modelViewMatrix * vec4(vertex, 1.0)).xyz;
    N = normalize(normalMatrix * normal);
    V = normalize(-P);                   
    L = normalize(lightPosition.xyz - P); 
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}

#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform vec3 boundingBoxMin, boundingBoxMax;

uniform float t = 0.4;
uniform float scale = 4.;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    float c = mix(boundingBoxMin.y, boundingBoxMax.y, t);
	vec3 nouVertex;
	if (vertex.y < c) {
		mat4 rot = mat4(vec4(1, 0, 0, 0), vec4(0, scale, 0, 0), vec4(0, 0, 1, 0), vec4(0, 0, 0, 1));
    	nouVertex = (rot*vec4(vertex, 1.0)).xyz;
	}
	else{
		float delta = c * (scale - 1.);
		mat4 mov = mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(0, delta, 0, 1));
		nouVertex = (mov*vec4(vertex, 1.0)).xyz;
		}
    frontColor = vec4(color,1.0) * N.z;
    gl_Position = modelViewProjectionMatrix * vec4(nouVertex, 1.0);
}

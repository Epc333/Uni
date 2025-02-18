#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float time;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;
    float angle = max(0., (vertex.y - 0.5)) * sin(time);
	mat3 rotacio = mat3(vec3(1,0,0), vec3(0, cos(angle), sin(angle)), vec3(0, -sin(angle), cos(angle)));
	vec3 offset = vec3 (0.0, 1., 0.);
	vec3 nouVertex = rotacio * (vertex - offset) + offset;
    gl_Position = modelViewProjectionMatrix * vec4(nouVertex, 1.0);
}

#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform vec2 Min = vec2(-1, -1);
uniform vec2 Max = vec2(1, 1);

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;
	vec3 nouPos = vec3(0);
	nouPos.x = 2.0 * (texCoord.x - Min.x) / (Max.x - Min.x) - 1.0;
	nouPos.y =  2.0 * (texCoord.y - Min.y) / (Max.y - Min.y) - 1.0;
	
    gl_Position = vec4(nouPos, 1.0);
}

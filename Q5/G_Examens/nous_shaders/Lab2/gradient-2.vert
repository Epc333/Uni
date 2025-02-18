#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;



out vec4 frontColor;


uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

vec4 red = vec4(1,0,0,1);
vec4 yellow = vec4(1,1,0,1);
vec4 green = vec4(0,1,0,1);
vec4 cian = vec4(0,1,1,1);
vec4 blue = vec4(0,0,1,1);

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
	float y = ((gl_Position.y / gl_Position.w) + 1. )/ 2.;
	if (y < 0.25) frontColor = mix(red, yellow, y / 0.25); 
    else if (y < 0.5) frontColor = mix(yellow, green, (y - 0.25)/0.25);
    else if (y < 0.75) frontColor = mix(green, cian, (y - 0.5)/0.25);
    else frontColor = mix(cian, blue, (y - .75)/.25);
}

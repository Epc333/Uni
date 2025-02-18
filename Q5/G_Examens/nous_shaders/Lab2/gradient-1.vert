#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform vec3 boundingBoxMin, boundingBoxMax;

vec4 red = vec4(1,0,0,1);
vec4 yellow = vec4(1,1,0,1);
vec4 green = vec4(0,1,0,1);
vec4 cian = vec4(0,1,1,1);
vec4 blue = vec4(0,0,1,1);


void main()
{
    float yMin = boundingBoxMin.y;
    float yMax = boundingBoxMax.y;
    float y = vertex.y;
    float yi = (y - yMin)/(yMax - yMin);
    
    if (yi < .25) frontColor = mix(red, yellow, yi / .25); 
    else if (yi < .5) frontColor = mix(yellow, green, (yi - .25)/.25);
    else if (yi < .75) frontColor = mix(green, cian, (yi - .5)/.25);
    else frontColor = mix(cian, blue, (yi - .75)/.25);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}

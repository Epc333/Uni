#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

uniform sampler2D noise0;
uniform sampler2D rock1;
uniform sampler2D grass2;

void main()
{
	float soroll = texture(noise0, vtexCoord).r;
	vec4 rockColor = texture(rock1, vtexCoord);
    vec4 grassColor = texture(grass2, vtexCoord);
	fragColor = mix(rockColor, grassColor, soroll);
} 

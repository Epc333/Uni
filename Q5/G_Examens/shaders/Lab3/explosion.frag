#version 330 core

in vec2 vtexCoord;
in vec4 frontColor;
out vec4 fragColor;

uniform sampler2D explosion; 
uniform float time;

void main()
{
	int frame = int(30*time) % 48;
	vec2 offset = vec2(1. / 8 * (frame%8), - 1. / 6 * (frame/8));
	vec2 coord = vtexCoord * vec2(1. / 8, 1. / 6) - vec2(0, 1. / 6);
    fragColor = frontColor * texture(explosion, vec2(coord + offset));
    fragColor = fragColor.a * fragColor;
}

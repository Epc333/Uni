#version 330 core

in vec2 vtexCoord;
in vec4 frontColor;
out vec4 fragColor;

uniform float time;
uniform sampler2D explosion;

void main()
{
	int frame = int(30*time) % 48;
	float x = frame % 8;
	float y = frame / 8;
	vec2 offset = vec2(x/8., -y/6.);
	vec2 coord = vtexCoord * vec2(1./8, 1./6) - vec2(0, 1. / 6);;
	
    fragColor = frontColor * texture(explosion, coord + offset);
	fragColor = fragColor.a * fragColor;
}

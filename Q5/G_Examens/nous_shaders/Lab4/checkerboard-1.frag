#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

vec4 grey = vec4(0.8);
vec4 black = vec4(0.);

void main()
{
	int x = int(mod(8*vtexCoord.x, 2));
	int y = int(mod(8*vtexCoord.y, 2));
	if (x == y) fragColor = grey;
	else fragColor = black;
 
}

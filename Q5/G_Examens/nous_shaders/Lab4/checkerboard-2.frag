#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform float n = 8; 

void main()
{
	vec4 grey = vec4(0.8);
	float x = vtexCoord.x;
	float y = vtexCoord.y;
	
	if (int(mod (n*x, 2)) ==  int(mod (n*y, 2))) fragColor = grey;
	else 
		fragColor = vec4(0.0);
}


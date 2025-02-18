#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform bool classic = true;

vec4 red = vec4(1., 0., 0., 1.);
vec4 white = vec4 (1.);
const float pi = acos(-1);

void main()
{
	vec2 centre = vec2(0.5, 0.5);
	vec2 u = vtexCoord - centre;
	float angle = atan(u.x , u.y);
	float d = distance(centre, vtexCoord);
	if (step(0.2, d) == 0) fragColor = red;
	else if (!classic && mod(angle/(pi/16)+0.5, 2) < 1) fragColor = red;
    else fragColor = white;
}

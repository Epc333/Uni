#version 330 core

in vec2 vtexCoord;
in vec4 frontColor;
out vec4 fragColor;

vec4 red = vec4(1., 0., 0., 1.);
vec4 white = vec4(1.);

const float pi = acos(-1);

uniform bool classic = true;

void main()
{
	vec2 C = vec2(0.5);
	float d = distance (C, vtexCoord);
	float f = step(d, 0.2);
	float angle = pi / 16.;
	vec2 u = vtexCoord - C;
	float frag = atan (u.t, u.s);
	if (d <= 0.2) fragColor = red;
	else if (!classic && mod(frag/angle + 0.5, 2) < 1) fragColor = red;
	else fragColor = white;
}

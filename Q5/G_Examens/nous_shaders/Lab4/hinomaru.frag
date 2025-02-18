#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

vec4 red = vec4(1., 0., 0., 1.);
vec4 white = vec4(1.);

void main (){
	vec2 C = vec2(0.5,0.5);
	float d = distance(C, vtexCoord);
	float f = smoothstep(0.2, 0.205, d);
	fragColor = mix (red, white, f);

}

/*
void main()
{
	vec2 C = vec2(0.5, 0.5);
	if (distance(C, vtexCoord) <= 0.2) fragColor = red;
	else fragColor = white;
}*/

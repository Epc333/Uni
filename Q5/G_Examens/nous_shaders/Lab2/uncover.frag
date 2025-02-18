#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in float pos;

uniform float time;

vec4 blue = vec4(0,0,1,1);

void main()
{
	if (time == 0.) discard;
	else if (pos < time - 1.) fragColor = blue;
    else discard;
}

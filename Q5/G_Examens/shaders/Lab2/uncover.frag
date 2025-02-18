#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec3 pos;

uniform float time;

void main()
{	
	if (time == 0.) discard;
	else if (pos.x < time - 1.) fragColor = vec4 (0.,0.,1.,1.);
    else discard;
}

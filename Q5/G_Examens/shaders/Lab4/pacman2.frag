#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 camp;

uniform sampler2D colormap;

void pintarMarge(){
	vec2 pos;
	if (camp.s < 1 && camp.t < 1) pos = vec2(5./6. - fract(camp.s)/6, 1 - fract(camp.t));
	else if (camp.s < 1 && camp.t > 14) pos = vec2(5./6. - fract(camp.s)/6, fract(camp.t));
	else if (camp.s > 14 && camp.t < 1) pos = vec2(5./6. - fract(camp.t)/6, fract(camp.s));
	else if (camp.s > 14 && camp.t > 14) pos = vec2(4./6. + fract(camp.s)/6, fract(camp.t));
	else if (camp.s < 1 || camp.s > 14) pos = vec2(0.5 + fract(camp.t)/6, fract(camp.s));
	else if (camp.t < 1 || camp.t > 14) pos = vec2(0.5 + fract(camp.s)/6, fract(camp.t));
	fragColor = texture(colormap, pos);
}

void paintGhost() {
	vec2 pos;
	pos = vec2 (fract(camp.t)/6, 1 - fract(camp.s));
	fragColor = texture(colormap, pos);
}

void main()
{
	if (camp.s < 1 || camp.s > 14 || camp.t < 1 || camp.t > 14) pintarMarge();
	else if (camp.s < 6 && camp.s > 5 && camp.t > 4 && camp.t < 6) paintGhost();
    else fragColor = frontColor;
}

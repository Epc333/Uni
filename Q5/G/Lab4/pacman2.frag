#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

uniform sampler2D colormap;

void pintarCantonades(int offset) {
	vec2 tex;	
	
	// Canonada inferior esquerra 
	if (vtexCoord.s < 1 && vtexCoord.t < 1) tex = vec2(5./6. - fract(vtexCoord.s)/6, 1 - fract(vtexCoord.t));
	// Canonada superior esquerra
	else if (vtexCoord.s < 1 && vtexCoord.t > 14) tex = vec2(5./6. - fract(vtexCoord.s)/6, fract(vtexCoord.t));
	// Canonada inferior dreta
	else if (vtexCoord.s > 14 && vtexCoord.t < 1) tex = vec2(5./6. - fract(vtexCoord.t)/6, fract(vtexCoord.s));
	// Canonada superior dreta
	else if (vtexCoord.s > 14 && vtexCoord.t > 14) tex = vec2(2./3. + fract(vtexCoord.s)/6, fract(vtexCoord.t));
	// Canonada vertical
	else if (vtexCoord.s < 1 || vtexCoord.s > 14 || offset == 1) tex = vec2(0.5 + fract(vtexCoord.t)/6, fract(vtexCoord.s));
	// Canonada horitzontal
	else if (vtexCoord.t < 1 || vtexCoord.t > 14) tex = vec2(0.5 + fract(vtexCoord.s)/6, fract(vtexCoord.t));
	// Pintem la canonada
	fragColor = texture(colormap, tex);
}

void pintarFantasma(int b) {
	vec2 tex;
	if (b == 0) tex = vec2(fract(vtexCoord.s)/6, fract(vtexCoord.t));
	else if (b == 1) tex = vec2(fract(vtexCoord.t)/6, 1 - fract(vtexCoord.s));
	fragColor = texture(colormap, tex);
}

void pintarPacman() {
	vec2 tex = vec2(1./6. + fract(vtexCoord.s)/6, fract(vtexCoord.t));
	fragColor = texture(colormap, tex);
}

void pintarPildora() {
	vec2 tex = vec2(5./6. + fract(vtexCoord.s)/6, fract(vtexCoord.t));
	fragColor = texture(colormap, tex);
}

void main() {
	if (vtexCoord.s < 1 || vtexCoord.s > 14 || vtexCoord.t < 1 || vtexCoord.t > 14) pintarCantonades(0);
	else if (vtexCoord.s < 6 && vtexCoord.s > 5 && vtexCoord.t > 1 && vtexCoord.t < 2) pintarFantasma(0);
	else if (vtexCoord.s < 8 && vtexCoord.s > 7 && vtexCoord.t > 3 && vtexCoord.t < 4) pintarFantasma(1);
	else if (vtexCoord.s < 5 && vtexCoord.s > 4 && vtexCoord.t > 1 && vtexCoord.t < 2) pintarPacman();
	else if ((int(vtexCoord.s) % 2) != 0 || (vtexCoord.t < 8 && vtexCoord.t > 7) || (vtexCoord.t > 13 && vtexCoord.t < 14) || (vtexCoord.t > 1 && vtexCoord.t < 2)) pintarPildora();
    else pintarCantonades(1);
}

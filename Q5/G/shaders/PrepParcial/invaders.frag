#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

uniform sampler2D colormap;

void pintarFatasma(int num){
	float x = float(num % 4) / 4.0;
    float y = float(num / 4) / 4.0; 
    vec2 tex = vec2(x + fract(vtexCoord.s) / 4.0, y + fract(vtexCoord.t) / 4.0);
    fragColor = texture(colormap, tex);
}

bool pintarEscut(float x) {
    // Inicialitzar l'array correctament
    float escut[4] = float[4](2.5, 5.5, 8.5, 12.5);

    for (int i = 0; i < 4; ++i) {
        // Comprovar si x està a prop de cada valor de l'array escut
        if (escut[i] - 0.5 < x && escut[i] + 0.5 > x) {
            return true;
        }
    }
    return false;
}

void main()
{
	if (vtexCoord.s < 1 || vtexCoord.s > 14 || vtexCoord.t < 1 || vtexCoord.t > 14) fragColor = vec4(0.);
	else if (vtexCoord.t > 13 && vtexCoord.t < 14) pintarFatasma(4);
	else if (vtexCoord.t > 12 && vtexCoord.t < 13) pintarFatasma(1);
	else if (vtexCoord.t > 11 && vtexCoord.t < 12) pintarFatasma(0);
	else if (vtexCoord.t > 10 && vtexCoord.t < 11) pintarFatasma(9);
	else if (vtexCoord.t > 9 && vtexCoord.t < 10) pintarFatasma(12);
	else if (vtexCoord.t > 8 && vtexCoord.t < 9) pintarFatasma(15);
	else if (vtexCoord.t > 7 && vtexCoord.t < 8) pintarFatasma(6);
	else if (vtexCoord.t > 6 && vtexCoord.t < 7) pintarFatasma(13);
	else if (vtexCoord.t > 4 && vtexCoord.t < 5 && pintarEscut(vtexCoord.s)) pintarFatasma(3);
    else  fragColor = vec4(0.);
}

#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D fons;
uniform sampler2D noise1;

uniform float time;

void main()
{
	vec2 noiseSample = texture(noise1, vtexCoord).rg;
 	float offsetS = 0.08 * time;  // Offset a l'eix s (u)
    float offsetT = 0.07 * time;  // Offset a l'eix t (v)
	vec2 perturbedCoords = vtexCoord + vec2(0.003, -0.005) * (vec2(offsetS, offsetT) + noiseSample);
    fragColor = texture(fons, perturbedCoords);
}

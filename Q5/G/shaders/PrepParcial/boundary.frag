#version 330 core

in vec3 N, P; 
out vec4 fragColor;

uniform float edge0 = 0.35;
uniform float edge1 = 0.4;

void main()
{
	vec3 V = normalize(-P);
	vec3 vN = normalize(N);
	float c = dot(vN, V);
    fragColor = vec4(smoothstep(edge0, edge1, c));
}

#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec3 fvertex;



void main()
{
    vec3 dFdxpos = dFdx(fvertex.xyz);
    vec3 dFdypos = dFdy(fvertex.xyz);
    vec3 N = normalize(cross(dFdxpos, dFdypos));
    fragColor = frontColor * N.z;
}

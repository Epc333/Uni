#version 330 core

in vec3 gnormal;
out vec4 fragColor;

void main()
{
    fragColor = vec4(vec3(gnormal.z), 1.0);
}

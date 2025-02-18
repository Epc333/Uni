#version 330 core

in vec3 vertex;
in vec3 colors;
out vec3 vs_color;
uniform float scl;
uniform mat4 TG;


void main()  {
    vs_color = colors;
    gl_Position = TG * vec4 ((vertex), 1.0);
}

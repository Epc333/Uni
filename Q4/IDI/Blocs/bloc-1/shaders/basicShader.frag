#version 330 core

in vec3 vs_color;
out vec4 FragColor;

void main() {
    FragColor = vec4(vs_color, 1);
}


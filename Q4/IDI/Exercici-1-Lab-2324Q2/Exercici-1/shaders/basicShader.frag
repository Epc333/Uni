#version 330 core

out vec4 FragColor;
uniform vec3 color_fs;

void main() {
    FragColor = vec4(color_fs, 1);
}

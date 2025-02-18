#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;
out vec2 gTexCoord; // Coordenadas de textura para el FS

uniform float size = 0.07;
uniform float depth = -0.01;

void main(void)
{
    // Emitir el triángulo original
    for (int i = 0; i < 3; i++)
    {
        gfrontColor = vfrontColor[i];
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    EndPrimitive();

    // Calcular el centro del triángulo en clip space
    vec3 C;
    C.x = (gl_in[0].gl_Position.x + gl_in[1].gl_Position.x + gl_in[2].gl_Position.x) / 3.0;
    C.y = (gl_in[0].gl_Position.y + gl_in[1].gl_Position.y + gl_in[2].gl_Position.y) / 3.0;
    C.z = 1.0-0.07;

    // Vértice superior derecho
    gfrontColor = vec4(1.0, 1.0, 0.0, 1.0); // Color amarillo
    gTexCoord = vec2(1.0, 1.0); // Coordenadas de textura
    gl_Position = vec4(C + vec3(size, size, 0.0), 1.0);
    EmitVertex();

    // Vértice superior izquierdo
    gTexCoord = vec2(0.0, 1.0);
    gl_Position = vec4(C + vec3(-size, size, 0.0), 1.0);
    EmitVertex();

    // Vértice inferior derecho
    gTexCoord = vec2(1.0, 0.0);
    gl_Position = vec4(C + vec3(size, -size, 0.0), 1.0);
    EmitVertex();

    // Vértice inferior izquierdo
    gTexCoord = vec2(0.0, 0.0);
    gl_Position = vec4(C + vec3(-size, -size, 0.0), 1.0);
    EmitVertex();

    EndPrimitive();
}

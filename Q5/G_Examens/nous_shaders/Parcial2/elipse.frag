#version 330 core

out vec4 fragColor;
in vec2 vtexCoord;

// Centre de l'el·lipse
uniform vec2 center = vec2(0.5, 0.5);
// Radi en cada eix
uniform float radiusX = 0.05; // Radi en l'eix X
uniform float radiusY = 0.1; // Radi en l'eix Y

void main() {
    // Coordenades relatives al centre de l'el·lipse
    vec2 pos = vtexCoord - center;
    
    // Escalar les coordenades per obtenir la forma de l'el·lipse
    float distanceFromCenter = (pos.x * pos.x) / (radiusX * radiusX) + (pos.y * pos.y) / (radiusY * radiusY);
    
    // Si el punt està dins de l'el·lipse, dibuixa-ho amb un color
    if (distanceFromCenter <= 1.0)
        fragColor = vec4(1.0, 0.6, 1, 1.0); // Color de l'el·lipse
    else
        fragColor = vec4(0.0); // Color de fons (transparent o negre)
}


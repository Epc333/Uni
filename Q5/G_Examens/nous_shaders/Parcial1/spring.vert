 #version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float time;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(vec3(N.z),1.0);
    vtexCoord = texCoord;
    vec3 V;
    float t = mod(time, 3.5);

	if (t < 0.5)
		V = vertex * pow(t/0.5, 3);
	else 
		V = vertex * (3.5 - t) / 3.;
    
    gl_Position = modelViewProjectionMatrix * vec4(V, 1.0);
}

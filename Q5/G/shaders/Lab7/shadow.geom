#version 330 core
		
layout(triangles) in;
layout(triangle_strip, max_vertices = 6) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform vec3 boundingBoxMin;

void main( void )
{
	// Triangle Original
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix * gl_in[i].gl_Position;
		EmitVertex();
	}
	EndPrimitive();

	// Sombra
	for (int i = 0; i < 3; i++) {
		gfrontColor = vec4(0.0, 0.0, 0.0, 1.0);
		vec4 shadowVertex = gl_in[i].gl_Position;
		shadowVertex.y = boundingBoxMin.y;
		gl_Position = modelViewProjectionMatrix * shadowVertex;
		EmitVertex();
	}
	EndPrimitive();
}

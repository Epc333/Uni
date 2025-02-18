#version 330 core
		
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform vec3 boundingBoxMin, boundingBoxMax;

vec4 Cyan = vec4(0., 1., 1., 1.);

void main() {
	// Triangle Original
	for (int i = 0; i < 3; i++) {
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix * gl_in[i].gl_Position;
		EmitVertex();
	}
	EndPrimitive();

	// Sombra
	for (int i = 0; i < 3; i++) {
		gfrontColor = vec4(0., 0., 0., 1.);
		vec4 v = gl_in[i].gl_Position;
		v.y = boundingBoxMin.y;
		gl_Position = modelViewProjectionMatrix * v;
		EmitVertex();
	}
	EndPrimitive();

	if (gl_PrimitiveIDIn == 0) {
		vec3 C = (boundingBoxMax + boundingBoxMin) * 0.5;  // Centre
		float R = length(boundingBoxMax - boundingBoxMin) * 0.5;  
		float y = boundingBoxMin.y - 0.01; 

		gfrontColor = Cyan;
		
		gl_Position = modelViewProjectionMatrix * vec4(C.x - R, y, C.z - R, 1.0);
		EmitVertex();
		gl_Position = modelViewProjectionMatrix * vec4(C.x - R, y, C.z + R, 1.0);
		EmitVertex();
		gl_Position = modelViewProjectionMatrix * vec4(C.x + R, y, C.z - R, 1.0);
		EmitVertex();
		EndPrimitive();
		
		gl_Position = modelViewProjectionMatrix * vec4(C.x + R, y, C.z - R, 1.0);
		EmitVertex();
		gl_Position = modelViewProjectionMatrix * vec4(C.x - R, y, C.z + R, 1.0);
		EmitVertex();
		gl_Position = modelViewProjectionMatrix * vec4(C.x + R, y, C.z + R, 1.0);
		EmitVertex();
		EndPrimitive();
	}
}

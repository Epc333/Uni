#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec3 vnormal[];
out vec3 gnormal;

uniform mat4 modelViewProjectionMatrix;
uniform float d = 0.5;

void main( void )
{
	for( int i = 0 ; i < 3 ; i++ )
	{
		gl_Position = modelViewProjectionMatrix * (gl_in[i].gl_Position);
		EmitVertex();
	}

    EndPrimitive();

    vec3 N = normalize((vnormal[0] + vnormal[1] + vnormal[2])/3.0);

    for (int i = 0; i < 3; ++i) {
        gnormal = N;
		gl_Position = modelViewProjectionMatrix * (gl_in[i].gl_Position + vec4(d*N, 0.0));
		EmitVertex();
    }

    EndPrimitive();

    for (int i = 0; i < 3; ++i) {
        int j = (i+1) % 3;

        vec4 V1, V2, V3, V4;
        V1 = modelViewProjectionMatrix * (gl_in[i].gl_Position + vec4(d*N, 0.0));
        V2 = modelViewProjectionMatrix * (gl_in[j].gl_Position + vec4(d*N, 0.0));
        V3 = modelViewProjectionMatrix * (gl_in[i].gl_Position);
        V4 = modelViewProjectionMatrix * (gl_in[j].gl_Position);

        vec3 edge1 = V2.xyz - V1.xyz;
        vec3 edge2 = V3.xyz - V1.xyz;
        gnormal = normalize(cross(edge2, edge1));


		gl_Position = V1;
		EmitVertex();

		gl_Position = V2;
		EmitVertex();

        gl_Position = V3;
		EmitVertex();

        gl_Position = V4;
		EmitVertex();

        EndPrimitive();
    }
}

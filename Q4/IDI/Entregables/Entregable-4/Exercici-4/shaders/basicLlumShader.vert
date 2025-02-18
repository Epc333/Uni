#version 330 core

in vec3 vertex;
in vec3 normal;

in vec3  matamb;
in vec3  matdiff;
in vec3  matspec;
in float matshin;

uniform mat4 TG;
uniform mat4 Proj;
uniform mat4 View;

uniform vec3 colorCotxe;

out vec3  fmatamb;
out vec3  fmatdiff;
out vec3  fmatspec;
out float fmatshin;
out vec3  fvertex;
out vec3  fnormal;

uniform vec3 posFocusEsc;
out vec3 fposFocusEsc;

uniform vec3 posFocus2Esc;
out vec3 fposFocus2Esc;



void main()
{	
    // Passem les dades al fragment shader
    fmatamb  = matamb;
    if (colorCotxe == vec3(1., 0., 0.) || colorCotxe == vec3(0., 1., 0.))
       fmatdiff = matdiff * colorCotxe;
    else
        fmatdiff = matdiff;

    fmatspec = matspec;
    fmatshin = matshin;
    //fvertex = vertex; // CALCULEU CORRECTAMENT
    fvertex = (View * TG * vec4(vertex, 1.0)).xyz;
    mat3 normalMatrix = inverse (transpose(mat3(View * TG)));
    fnormal = normalize(normalMatrix*normal); // CALCULEU CORRECTAMENT

    fposFocusEsc = (View * vec4(posFocusEsc,1.)).xyz;   //Passem posFocu en SCO
    fposFocus2Esc = (View * vec4(posFocus2Esc,1.)).xyz; 

    gl_Position = Proj * vec4(fvertex, 1);
}

#version 330 core

//in vec3 fcolor;
out vec4 FragColor;

in vec3 NSCOFS;
in vec4 vSCOFS;
in vec3 LSCOFS;

in vec3 matdiffFS;
in vec3 matspecFS;
in vec3 matambFS;
in float matshinFS;

//uniform vec3 posFocus;
uniform vec3 colorFocus;

vec3 llumAmbient = vec3(0.2, 0.2, 0.2);

vec3 Ambient() {
    return llumAmbient * matambFS;
}

vec3 Difus (vec3 NormSCO, vec3 L, vec3 colFocus) 
{
    // Tant sols retorna el terme difús
    // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
    vec3 colRes = vec3(0);
    // Càlcul component difusa, si n'hi ha
    if (dot (L, NormSCO) > 0)
      colRes = colFocus * matdiffFS * dot (L, NormSCO);
    return (colRes);
}

vec3 Especular (vec3 NormSCO, vec3 L, vec4 vertSCO, vec3 colFocus) 
{
    // Tant sols retorna el terme especular!
    // Els vectors rebuts com a paràmetres (NormSCO i L) estan normalitzats
    vec3 colRes = vec3 (0);
    // Si la llum ve de darrera o el material és mate no fem res
    if ((dot(NormSCO,L) < 0) || (matshinFS == 0))
      return colRes;  // no hi ha component especular

    // Calculem R i V
    vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
    vec3 V = normalize(-vertSCO.xyz); // perquè la càmera està a (0,0,0) en SCO

    if (dot(R, V) < 0)
      return colRes;  // no hi ha component especular
    
    // Calculem i retornem la component especular
    float shine = pow(max(0.0, dot(R, V)), matshinFS);
    return (matspecFS * colFocus * shine); 
}

void main()
{	
	vec3 fcolor = Ambient() + Difus(NSCOFS, LSCOFS, colorFocus) + Especular(NSCOFS, LSCOFS, vSCOFS, colorFocus);
	FragColor = vec4(fcolor,1);	
}

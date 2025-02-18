#version 330 core

in vec3  fmatamb;
in vec3  fmatdiff;
in vec3  fmatspec;
in float fmatshin;
in vec3  fvertex;
in vec3  fnormal;

vec3 colorFocus = vec3(0.8);
vec3 colorEsc = vec3(0.6, 0.6, 0);
vec3 posFocusCam = vec3(0.);

const vec3 llumAmbient = vec3(0.1);

in vec3 fposFocusEsc;
in vec3 fposFocus2Esc;
uniform vec3 fcolorFocus;

uniform bool llum;

out vec4 FragColor;


vec3 Ambient() {
  return llumAmbient*fmatamb;
}

vec3 Difus (vec3 NormSCO, vec3 L, vec3 colFocus)
{
  // Fixeu-vos que SOLS es retorna el terme de Lambert!
  // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
  vec3 colRes = vec3(0);
  if (dot (L, NormSCO) > 0)
    colRes = colFocus * fmatdiff * dot (L, NormSCO);
  return (colRes);
}

vec3 Especular (vec3 NormSCO, vec3 L, vec3 vertSCO, vec3 colFocus)
{
  // Fixeu-vos que SOLS es retorna el terme especular!
  // Assumim que els vectors estan normalitzats
  vec3 colRes = vec3 (0);
  // Si la llum ve de darrera o el material és mate no fem res
  if ((dot(NormSCO,L) < 0) || (fmatshin == 0))
    return colRes;  // no hi ha component especular

  vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
  vec3 V = normalize(-vertSCO); // perquè la càmera està a (0,0,0) en SCO

  if (dot(R, V) < 0)
    return colRes;  // no hi ha component especular

  float shine = pow(max(0.0, dot(R, V)), fmatshin);
  return (colRes + fmatspec * colFocus * shine);
}

void main()
{
    vec3 LSCOEsc = normalize(fposFocusEsc - fvertex);
    vec3 LSCO2Esc = normalize(fposFocus2Esc - fvertex);
    vec3 LSCOCam = normalize(posFocusCam - fvertex);
    vec3 normalSCO = normalize(fnormal);

    vec3 fcolor = Ambient() + Difus(normalSCO, LSCOEsc, colorEsc) + Especular(normalSCO, LSCOEsc, fvertex, colorEsc);
    fcolor += Difus(normalSCO, LSCO2Esc, colorEsc) + Especular(normalSCO, LSCO2Esc, fvertex, colorEsc);

    if (llum) fcolor += Difus(normalSCO, LSCOCam, colorFocus) + Especular(normalSCO, LSCOCam, fvertex, colorFocus);
    
    FragColor = vec4(fcolor, 1);
}

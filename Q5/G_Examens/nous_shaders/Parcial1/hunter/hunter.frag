#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform vec2 mousePosition;
uniform sampler2D jungla;
uniform vec2 viewport; 
uniform float magnific = 3;

vec4 blurImage( in vec2 coords )
{
    float Pi = 6.28318530718; // Pi*2
    float Directions = 16.0; // BLUR DIRECTIONS (Default 16.0 - More is better but slower)
    float Quality = 8.0; // BLUR QUALITY (Default 4.0 - More is better but slower)
    float Size = 10.0; // BLUR SIZE (Radius)
   
    vec2 Radius = Size/viewport;

    vec4 Color = texture(jungla, coords);
    for( float d=0.0; d<Pi; d+=Pi/Directions)
    {
        float cd = cos(d);
        float sd = sin(d);
		for(float i=1.0/Quality; i<=1.0; i+=1.0/Quality)
        {
			Color += texture(jungla, coords+vec2(cd,sd)*Radius*i);		
        }
    }
    
    // Output to screen
    Color /= Quality * Directions - 15.0;
    return  Color;
} 

vec4 zoom(in vec2 coords) {
    // Calculate the relative position of the current fragment to the mouse position
    vec2 P = coords * viewport - mousePosition;
    float dist = length(P);
    float zoomAplicat = 1. + magnific * dist/viewport.x;
    vec2 nouPunt = mousePosition + (P / zoomAplicat);
    vec2 normalitzat = nouPunt/viewport;
   
    return texture(jungla, normalitzat);
}

bool pintarBinocles (){
	vec2 pixel = vtexCoord * viewport;
	vec2 cercle1 = mousePosition.xy - vec2(80, 0);
	vec2 cercle2 = mousePosition.xy + vec2(80, 0);
	float dist1 = distance (cercle1, pixel);
	float dist2 = distance (cercle2, pixel);
	if (dist1 < 100 || dist2 < 100) {
		fragColor = zoom(vtexCoord);
		return true;
	}else if (dist1 < 105 || dist2 < 105) {
		fragColor = vec4(vec3(0), 1.);
		return true;
	}
	return false; 

}

void main()
{
	bool pintat = pintarBinocles();
	if (!pintat) fragColor = blurImage(vtexCoord);
}

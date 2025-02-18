#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D jungla;
uniform vec2 viewport;
uniform vec2 mousePosition;
uniform float magnific = 3.0;

// adaptat de https://www.shadertoy.com/view/Xltfzj. 
// no és realment Gaussià
// **requereix** que hi hagi declarat un sampler2D jungla!
// retorna el color corresponent a les coordenades de textura coords.
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

//P must be in clipping space
bool isBinocularBody(vec2 P) {
    vec2 c1, c2; //Centers of both circles
    c1 = mousePosition + vec2(80.0, 0);
    c2 = mousePosition - vec2(80.0, 0);
    float d1, d2; //Distance to c1 and c2
    d1 = distance(c1, P*viewport);
    d2 = distance(c2, P*viewport);

    return d1 < 100.0 || d2 < 100.0;
}

//P must be in clipping space
bool isBinocularEdge(vec2 F) {
    vec2 c1, c2; //Centers of both circles
    c1 = mousePosition + vec2(80.0, 0);
    c2 = mousePosition - vec2(80.0, 0);
    float d1, d2; //Distance to c1 and c2
    d1 = distance(c1, F*viewport);
    d2 = distance(c2, F*viewport);

    return (d1 < 105.0 && d1 > 100.0)  ||  (d2 < 105.0 && d2 > 100.0);
}

vec4 getMagificColor(vec2 F) {
    vec2 mpNorm = mousePosition/viewport;
    vec2 st;
    st.s = -((mpNorm.x - F.x)/magnific - mpNorm.x);
    st.t = -((mpNorm.y - F.y)/magnific - mpNorm.y);
    return texture(jungla, st);
}


void main()
{
    if (isBinocularBody(vtexCoord))
        fragColor = getMagificColor(vtexCoord);
    else if (isBinocularEdge(vtexCoord))
        fragColor = vec4(0.0, 0.0, 0.0, 1.0);
    else
        fragColor = blurImage(vtexCoord);
}

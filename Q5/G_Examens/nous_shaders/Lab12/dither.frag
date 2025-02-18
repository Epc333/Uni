#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform int mode = 2;

const vec4 BLACK = vec4(0.,0.,0.,1.);
const vec4 WHITE = vec4(1.);

void main()
{
    float intensitat = frontColor.x;

    if (mode == 2){
        if (int(mod(int(gl_FragCoord.x), 2)) == 0 && int(mod(int(gl_FragCoord.y), 2)) == 0) intensitat -= 0.5;
        else if (int(mod(int(gl_FragCoord.x), 2)) == 0 && int(mod(int(gl_FragCoord.y), 2)) == 1) intensitat += 0.25;
        else if (int(mod(int(gl_FragCoord.x), 2)) == 1 && int(mod(int(gl_FragCoord.y), 2)) == 1) intensitat -= 0.25;
    }

    if (intensitat < 0.5)
        fragColor = BLACK;
    else
        fragColor = WHITE;
   
}

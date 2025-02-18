#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform int mode = 2; 

void main()
{
    float ilum = length(frontColor.a);

    if (mode == 2) {
        if (mod(gl_FragCoord.x, 2) < 1) {
            if (mod(gl_FragCoord.y, 2) < 1)
                ilum -= 0.5;
            else
                ilum += 0.25;
        }
        else {
            if (mod(gl_FragCoord.y, 2) > 1)
                ilum -= 0.25;
        }
    }

    if (ilum < 0.5)
        fragColor = vec4(0.0, 0.0, 0.0, 1.0);
    else
        fragColor = vec4(1.0);
}

#version 330 core

in vec4 gfrontColor;
in vec2 gTexCoord;
out vec4 fragColor;

vec4 BLACK = vec4(0.0, 0.0, 0.0, 1.0);

void main()
{
    fragColor = gfrontColor;

    vec2 st = gTexCoord*7.0;
    if (st.t < 6.0 && st.t > 1.0 && st.s > 2.0 && st.s < 3.0)
        fragColor = BLACK;

    if (st.t < 6.0 && st.t > 5.0 && st.s > 3.0 && st.s < 5.0)
        fragColor = BLACK;

    if (st.t < 4.0 && st.t > 3.0 && st.s > 2.0 && st.s < 4.0)
        fragColor = BLACK;
}

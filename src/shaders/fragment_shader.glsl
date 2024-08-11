#version 330 core
out vec4 FragColor;

uniform float time;
uniform vec2 dims;
uniform vec2 mouse;

void main()
{
    vec2 uv = gl_FragCoord.xy / dims;
    uv.y = 1.0 - uv.y;

    float dist = distance(uv, mouse);
    dist = sin(dist * 10.0 + time) * 0.5 + 0.5;
    FragColor = vec4(dist, dist, dist, 1.0);
}
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(gl_FragCoord.x / 800.0, gl_FragCoord.y / 600.0, 0.5, 1.0);
}
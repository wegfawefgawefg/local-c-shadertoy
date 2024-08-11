#version 330 core
out vec4 FragColor;
uniform float time;
uniform vec2 dims;
uniform vec2 mouse;
uniform vec2 squarePositions[16];
uniform int numSquares;

float metaball(vec2 uv, vec2 center, float size) {
    float dist = distance(uv, center);
    return size / (dist * dist);
}

void main()
{
    vec2 uv = gl_FragCoord.xy / dims;
    uv.y = 1.0 - uv.y;
    
    float metaValue = 0.0;
    
    // Calculate metaball value
    for (int i = 0; i < numSquares; i++) {
        metaValue += metaball(uv, squarePositions[i], 0.02);
    }
    
    // Create color based on metaball value
    vec3 color = vec3(0.0);
    // uncomment the following line for cool metaballs
    // metaValue = sin(metaValue * 10.0 + time) * 0.5 + 0.5 * metaValue;
    if (metaValue > 1.0) {
        float t = smoothstep(1.0, 1.5, metaValue);
        color = mix(vec3(1.0, 0.0, 0.0), vec3(1.0, 1.0, 0.0), t);
    }
    
    // Add mouse interaction
    // float mouseDist = distance(uv, mouse);
    // float mouseInfluence = 0.05 / (mouseDist * mouseDist);
    // color = mix(color, vec3(0.0, 1.0, 1.0), smoothstep(0.0, 1.0, mouseInfluence));
    
    FragColor = vec4(color, 1.0);
}
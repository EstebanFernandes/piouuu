#version 330 core

uniform vec2 u_resolution;
uniform sampler2D textureSampler;

out vec4 FragColor;

void main() {
    const float Pi = 6.28318530718; // Pi*2
    
    // GAUSSIAN BLUR SETTINGS
    const float Directions = 16.0; // BLUR DIRECTIONS (Default 16.0 - More is better but slower)
    const float Quality = 10.0; // BLUR QUALITY (Default 4.0 - More is better but slower)
    const float Size = 5.0; // BLUR SIZE (Radius)
    const float aaa = Pi / Directions;
    const float mu = 1.0 / Quality;
    vec2 Radius = Size / u_resolution.xy;
    
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = gl_FragCoord.xy / u_resolution.xy;
    // Pixel colour
    vec4 Color = texture(textureSampler, uv);
    
    // Blur calculations
    for (float d = 0.0; d < Pi; d += aaa) {
        for (float i = mu; i <= 1.0; i += mu) {
            Color += texture(textureSampler, uv + vec2(cos(d), sin(d)) * Radius * i);
        }
    }
    
    // Normalize the color
    Color /= (Quality * Directions);
    FragColor = Color;
}

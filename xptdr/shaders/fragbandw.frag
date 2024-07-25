#version 330 core

uniform vec2 u_resolution;
uniform sampler2D textureSampler;

out vec4 FragColor;

void main() {
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = gl_FragCoord.xy / u_resolution.xy;
    // Pixel colour
    vec4 color = texture(textureSampler, uv);
    // Convertir en niveaux de gris
    float gray = dot(color.rgb, vec3(0.299, 0.587, 0.114));
    FragColor = vec4(vec3(gray), color.a);
}
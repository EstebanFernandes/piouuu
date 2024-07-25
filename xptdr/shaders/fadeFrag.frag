#version 120
uniform sampler2D textureSampler;
uniform float time;
uniform float uAlphaChance;

void main()
{
    // lookup the pixel in the texture
    vec4 pixel = texture2D(textureSampler, gl_TexCoord[0].xy);

    // Générer un nombre aléatoire basé sur les coordonnées des pixels et le temps
    float randomValue = fract(sin(dot(gl_FragCoord.xy + vec2(time * 10.0, time * 10.0), vec2(12.9898, 78.233))) * 43758.5453);
     //float randomValued = fract(sin(dot(gl_FragCoord.xy + vec2(2*time * 10.0, 3*time * 10.0), vec2(12.9898, 78.233))) * 43758.5453);
    // Si la valeur aléatoire est inférieure à uAlphaChance, rendre le canal alpha à 0
    if (randomValue < uAlphaChance) {
        pixel.a = 0.0;
    }
    // multiply it by the color
    gl_FragColor = gl_Color * pixel;
}
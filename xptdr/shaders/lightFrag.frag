#version 460 

out vec4 FragColor;


uniform vec2 u_resolution;
uniform vec2 lightPoint;

uniform sampler2D texture;
uniform sampler2D shadowMask; // Texture de masque d'ombres
void main()
{
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = gl_FragCoord.xy/u_resolution.xy;
    vec2 lightUV = lightPoint.xy/u_resolution.xy;
    
    // Adjust for aspect ratio by scaling UV coordinates correctly
    float aspectRatio = u_resolution.x / u_resolution.y;
    vec2 scaledUV = vec2(uv.x * aspectRatio, uv.y);
    vec2 scaledLightUV = vec2(lightUV.x * aspectRatio, lightUV.y);

      // Base color from the texture
    vec3 col = texture2D(texture, uv).rgb;
    
    // Calculate distance from the light point
    float distanceFromLight = distance(scaledUV, scaledLightUV);
    
    // Light effect: closer to the light point, the brighter the color
    float lightIntensity = 0.1 / (distanceFromLight * distanceFromLight + 0.11); // Ajout de 0.01 pour éviter la division par zéro
    
    // Adjust the intensity for a more pronounced effect
   lightIntensity = clamp(lightIntensity, 0.0, 1.0);
    
    
   vec3 shadowColor = texture(shadowMask, uv).rgb;
    float shadow = 0.2126 * shadowColor.r + 0.7152 * shadowColor.g + 0.0722 * shadowColor.b;
    lightIntensity *= shadow;

    // Apply light effect to the base color
    vec3 lightColor = vec3(1, 1.0, 1.0); // White light color
    col = mix(col, lightColor, lightIntensity);
    // Output to screen
    FragColor = vec4(col,1.0);
}
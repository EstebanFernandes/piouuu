#version 460 

out vec4 FragColor;

in vec2 TexCoord;

uniform vec2 u_resolution;
uniform sampler2D textureSampler;

void main()
{
    vec4 color = texture(textureSampler, gl_FragCoord.xy/u_resolution.xy);
    // Convert to grayscale
    float gray = dot(color.rgb, vec3(0.299, 0.587, 0.114));
    FragColor = vec4(vec3(gray), color.a);
}
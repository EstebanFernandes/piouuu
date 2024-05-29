#version 120

precision mediump float;

uniform vec2 u_resolution;
uniform sampler2D texture;

void main(){
    
   const float Pi = 6.28318530718; // Pi*2
    
  // GAUSSIAN BLUR SETTINGS {{{
    const float Directions = 16.0; // BLUR DIRECTIONS (Default 16.0 - More is better but slower)
    const float Quality = 10.; // BLUR QUALITY (Default 4.0 - More is better but slower)
    const float Size = 5.0; // BLUR SIZE (Radius)
    // GAUSSIAN BLUR SETTINGS }}}
   const float aaa = Pi/Directions;
    const float mu =1.0/Quality;
    vec2 Radius = Size/u_resolution.xy;
    
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = gl_FragCoord.xy/u_resolution.xy;
    // Pixel colour
    vec4 Color = texture2D(texture, uv);
    
    // Blur calculations
    for( float d=0.0; d<Pi; d+=aaa)
    {
        
		for(float i=1.0/Quality; i<=1.0; i+=1.0/Quality)
        {
			Color += texture2D( texture, uv+vec2(cos(d),sin(d))*Radius*i);		
        }
    }
    
    // Output to screen
    Color /= Quality * Directions - 15.0;
    gl_FragColor =  Color;
}

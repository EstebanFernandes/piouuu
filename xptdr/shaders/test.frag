#version 120

precision mediump float;


uniform vec2 u_resolution;
uniform float u_time;
uniform float angle;
mat2 rotationMatrix(float angle)
{
	angle *= 3.14 / 180.0;
    float sine = sin(angle), cosine = cos(angle);
    return mat2( cosine, -sine, 
                 sine,    cosine );
}

vec2 mirrorTile(vec2 _st, float _zoom){
    _st *= _zoom;
    if (fract(_st.y * 0.5) > 0.5){
        _st.x = _st.x+0.5;
        _st.y = 1.0-_st.y;
    }
    return fract(_st);
}

vec3 fillY(vec2 _st, float _pct, float _antia, vec3 _color){
  float alpha = smoothstep(_pct -0.02- _antia, _pct, _st.y);
  return _color * alpha;
}


void main(){
  vec2 st = gl_FragCoord.xy/u_resolution.xy;
  float newAngle = mod(angle+u_time*1.3,360.);  
    st *= rotationMatrix( newAngle);
    st.y+=u_time*0.05;
    st.x+=u_time*-.1;
    vec3 color = 0.5 + 0.5*cos(u_time+st.xyx+vec3(0.317,0.585,4.000));
  st = mirrorTile(st*vec2(1.,2.),7.);
      
  float x = st.x*2.008;
  float a = floor(1.+sin(x*3.14));
  float b = floor(1.000+sin((x+1.000)*3.14));
  float f = fract(x);

  color =  fillY(st,mix(a,b,f),0.,color);
  gl_FragColor = vec4( color, 1.0 );
}

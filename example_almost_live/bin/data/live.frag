

#ifdef GL_ES
precision mediump float;
#endif

#define PI 3.14159265359
#define TWO_PI 6.28318530718

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;
uniform float u_var0;
uniform float u_var1;

float usin( float _time ){
    return (sin(_time) * 0.5)+0.5;
}

void main(){
  vec2 st = gl_FragCoord.xy/u_resolution.xy;
  
  vec3 color = vec3 (1.0, usin( u_time)*u_var0, 0.0 );
  gl_FragColor = vec4(color,1.0);
}

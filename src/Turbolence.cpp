
#include "Turbolence.h"

ofx::dotfrag::Turbolence::Turbolence() {
    name("turbolence");
    uniform( x.set("distort x", 0.0f, 0.0f, 1.0f), "u_amount_x" );
    uniform( y.set("distort y", 0.0f, 0.0f, 1.0f), "u_amount_y" );
    source( code );
}

const string ofx::dotfrag::Turbolence::code = OFXDOTFRAGSOURCE(

    #ifdef GL_ES
    precision mediump float;
    #endif

    uniform vec2 u_resolution;
    uniform float u_time;
    uniform sampler2D u_tex0;

    uniform float u_amount_x;
    uniform float u_amount_y;

    float rand(vec2 st, float t){
        return fract(sin(dot(st.xy + fract(t*0.0013) ,vec2(12.9898,78.233))) * 43758.5453);
    }

    void main(){
        vec2 st = gl_FragCoord.xy/u_resolution.xy;

        float amtx = u_amount_x * u_amount_x * 0.2;
        float amty = u_amount_y * u_amount_y * 0.2;

        st.x += (rand(st, u_time)*2.0 - 1.0) * amtx;  
        st.y += (rand(st, u_time)*2.0 - 1.0) * amty;
        
        vec4 source = texture2D(  u_tex0, st );

        gl_FragColor = source;
    }
    
); //OFXDOTFRAGSOURCE end


#include "InvertStrobe.h"

ofx::dotfrag::InvertStrobe::InvertStrobe() {
    name("invert strobe");
    timewarp();
    uniform( pulse.set("pulse", 1.0f, 0.0f, 1.0f), "u_pulse" );
    source( code );
}

const std::string ofx::dotfrag::InvertStrobe::code = OFXDOTFRAGSOURCE(

    #ifdef GL_ES
    precision mediump float;
    #endif

    uniform vec2 u_resolution;
    uniform float u_time;
    uniform sampler2D u_tex0;

    uniform float u_pulse;

    void main (void) {
        vec2 st = gl_FragCoord.xy/u_resolution;
        
        vec4 source = texture2D( u_tex0, st );
                
        float gate = step( u_pulse, fract( u_time*0.8 ) );
                
        vec3 invert = 1.0 - source.rgb;
        
        vec3 color = mix( invert, source.rgb, gate );
        
        gl_FragColor = vec4( color, source.a );
    }
    
); //OFXDOTFRAGSOURCE end

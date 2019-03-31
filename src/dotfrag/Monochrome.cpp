
#include "Monochrome.h"

ofx::dotfrag::Monochrome::Monochrome() {
    name("monochrome");
    uniform( low.set("low", 0.0f, 0.0f, 1.0f), "u_low" );
    uniform( high.set("high", 1.0f, 0.0f, 1.0f), "u_high" );
    source( code );
}


const std::string ofx::dotfrag::Monochrome::code = OFXDOTFRAGSOURCE(

    #ifdef GL_ES
    precision mediump float;
    #endif

    uniform vec2 u_resolution;
    uniform float u_time;
    uniform sampler2D u_tex0;
    
    uniform float u_low;    
    uniform float u_high;    

    void main (void) {
        vec2 st = gl_FragCoord.xy/u_resolution;
        
        vec4 source = texture2D( u_tex0, st );
        float luminance = source.r*0.299 + source.g*0.587 + source.b*0.114;	
        
        float range = u_high - u_low;
        float remapped = luminance - u_low;
        remapped = max( 0.0, remapped );
        remapped = min( remapped, range );
        remapped = remapped / range;
        
        gl_FragColor = vec4( vec3(remapped), source.a );
    }
    
); //OFXDOTFRAGSOURCE end

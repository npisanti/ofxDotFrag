
#include "Monochrome.h"

ofx::dotfrag::Monochrome::Monochrome() {
    name("monochrome");
    source( code );
}

const std::string ofx::dotfrag::Monochrome::code = OFXDOTFRAGSOURCE(

    #ifdef GL_ES
    precision mediump float;
    #endif

    uniform vec2 u_resolution;
    uniform float u_time;
    uniform sampler2D u_tex0;
    varying vec2 st;

    void main (void) {
        vec4 source = texture2D( u_tex0, st );
        float luminance = source.r*0.299 + source.g*0.587 + source.b*0.114;	
        gl_FragColor = vec4( vec3(luminance), source.a );
    }
    
); //OFXDOTFRAGSOURCE end

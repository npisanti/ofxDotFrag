
#include "EchoTrace.h"


ofx::dotfrag::EchoTrace::EchoTrace() {
    name("echotrace");
    pingpong(); // activate ping pong buffer
    uniform( gain.set("gain", 0.7f, 0.0f, 2.0f), "u_gain" );
    uniform( threshold.set("threshold", 0.55f, 0.0f, 1.0f), "u_threshold");
    uniform( invert.set("invert", false), "u_invert" );
    uniform( hardCutoff.set("hardcutoff", false), "u_hardcutoff" );
    source( code );
}


const string ofx::dotfrag::EchoTrace::code = OFXDOTFRAGSOURCE(

    #ifdef GL_ES
    precision mediump float;
    #endif

    uniform vec2 u_resolution;
    uniform float u_time;
    uniform sampler2D u_tex0;
    uniform sampler2D u_tex1;

    uniform float u_gain;
    uniform float u_threshold;
    uniform bool u_invert;
    uniform bool u_hardcutoff;

    void main (void) {
        
        vec2 st = gl_FragCoord.xy/u_resolution.xy;
        
        vec4 freshPixel = texture2D( u_tex0, st );
        vec4 stalePixel = texture2D( u_tex1, st );
        float brightLevel = 0.299*freshPixel.r +  0.587*freshPixel.g + 0.114*freshPixel.b;
        
        // invert
        if( u_invert ) brightLevel = 1.0 - brightLevel;
        
        brightLevel = brightLevel * u_gain;
        
        // hard cutof
        if(u_hardcutoff) brightLevel = step( u_threshold, brightLevel );

        gl_FragColor = mix( freshPixel, stalePixel, brightLevel);
        
        gl_FragColor = freshPixel;
    }

); //OFXDOTFRAGSOURCE end

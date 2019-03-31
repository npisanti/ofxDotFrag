
#include "ThreeTones.h"
	
ofx::dotfrag::ThreeTones::ThreeTones() {
    
    thresholds.resize(2);
    colors.resize(3);
    
    name("three tones");
    uniform( mix.set( "mix", 1.0f, 0.0f, 1.0f), "u_mix");
    uniform( thresholds[0].set("threshold 0 1", 0.0f, 0.0f, 1.0f), "u_low");
    uniform( thresholds[1].set("threshold 1 2", 0.4f, 0.0f, 1.0f), "u_middle" );
    uniform( fade.set("threshold fade", 0.1f, 0.0f, 0.3f), "u_fade" );
    
    uniform( colors[0].set( "color 0", ofColor(0), ofColor(0), ofColor(255)), "u_color_0" );
    uniform( colors[1].set( "color 1", ofColor(0, 255, 0), ofColor(0), ofColor(255)), "u_color_1" );
    uniform( colors[2].set( "color 2", ofColor(255), ofColor(0), ofColor(255)), "u_color_2" );

    source( code );
}

const std::string ofx::dotfrag::ThreeTones::code = OFXDOTFRAGSOURCE(

    #ifdef GL_ES
    precision mediump float;
    #endif

    uniform vec2 u_resolution;
    uniform float u_time;
    uniform sampler2D u_tex0;

    uniform float u_middle;
    uniform float u_low;
    uniform float u_mix;

    uniform vec3 u_color_0;
    uniform vec3 u_color_1;
    uniform vec3 u_color_2;
    
    uniform float u_fade;

    void main (void) {
        vec2 st = gl_FragCoord.xy/u_resolution;
        
        vec4 source = texture2D(u_tex0, st);	
        
        //Photometric/digital ITU BT.709:
        //float luminance = source.r*0.2126 + source.g*0.7152 + source.b*0.0722;
        
        //Digital ITU BT.601 (gives more weight to the R and B components):
        float luminance = source.r*0.299 + source.g*0.587 + source.b*0.114;	

        float lowstep = smoothstep( u_low, u_low+u_fade, luminance );
        float lightgate = smoothstep( u_middle, u_middle+u_fade, luminance );
        
        float shadowgate = (1.0-lowstep);
        float midgate = lowstep * (1.0-lightgate);
        
        vec3 color = u_color_0 * shadowgate + u_color_1*midgate + u_color_2*lightgate;
        color *= luminance; 
        
        gl_FragColor = vec4( mix(source.rgb, color, u_mix), source.a );
    }

); //OFXDOTFRAGSOURCE end


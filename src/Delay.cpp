
#include "Delay.h"


ofx::dotfrag::Delay::Delay() {
    name("video delay");
    framebuffer( 6 );
    uniform( feedback.set("feedback", 0.0f, 0.0f, 1.0f), "u_feedback" );
    uniform( blendmode.set("blendmode", 0, 0, 4), "u_blendmode" );
    source( code );
}


const std::string ofx::dotfrag::Delay::code = OFXDOTFRAGSOURCE(

    #ifdef GL_ES
    precision mediump float;
    #endif

    uniform vec2 u_resolution;
    uniform float u_time;
    
    uniform sampler2D u_tex0;
    uniform sampler2D u_tex1;
    varying vec2 st;
    
    uniform float u_feedback;
    uniform int u_blendmode;

    void main (void) {
        
        vec4 now = texture2D(u_tex0, st);
        vec4 delay = texture2D(u_tex1, st);
        
        float alpha = max( now.a, delay.a );
        
        if( u_blendmode==0 ){
            // screen
            vec3 screen = 1.0-((1.0-now.xyz)*(1.0-delay.xyz));
            gl_FragColor = vec4(now.xyz*(1.0-u_feedback) + screen*u_feedback, alpha);
        }else if( u_blendmode==1 ){
            // sum
            vec3 sum = min(now.xyz + delay.xyz*u_feedback, vec3(1.0));
            gl_FragColor = vec4( sum, alpha );
        }else if( u_blendmode==2 ){
            // lerp
            gl_FragColor = vec4(now.xyz*(1.0-u_feedback) + delay.xyz*u_feedback, alpha);
        }else if( u_blendmode==3 ){
            // blend max
            gl_FragColor = vec4( max(now.xyz, delay.xyz*u_feedback), alpha );
        }else{
            // blend min
            gl_FragColor = vec4( min(now.xyz, delay.xyz*u_feedback), alpha );
        }
    }

); //OFXDOTFRAGSOURCE end

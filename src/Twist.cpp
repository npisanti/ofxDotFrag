
#include "Twist.h"

ofx::dotfrag::Twist::Twist() {
    name("mirror");
    parameters.add( amount.set("amount", 0.5f, 0.0f, 1.0f) );
    parameters.add( variation.set("variation",  0.5f, 0.0f, 1.0f) );

    source( fragment );
}

void ofx::dotfrag::Twist::preshading( float w, float h ) {
    float rand = ofRandom( 1.005f-variation );
    shader.setUniform1f		("rand",        rand);
    shader.setUniform1f		("val1",        ofRandom(amount));
    shader.setUniform1f		("val2",        ofRandom(amount));
    shader.setUniform1f		("val3",        ofRandom(amount));
    shader.setUniform1f		("val4",        ofRandom(amount));
    shader.setUniform1f		("multx",       1.0f/(1.5325*rand*rand) );
    shader.setUniform1f		("multy",       1.0f/(2.5157*rand*rand) );
}

const std::string ofx::dotfrag::Twist::fragment = OFXDOTFRAGSOURCE(

    #ifdef GL_ES
    precision mediump float;
    #endif

    uniform vec2 u_resolution;
    uniform float u_time;
    uniform sampler2D u_tex0;
    uniform vec2 u_tex0Resolution;

    varying vec2 dt;

    uniform float rand;
    uniform float val1,val2,val3,val4;
    uniform float multx, multy;

    void main (void)
    {

        vec2 st = gl_FragCoord.xy/u_resolution.xy;
        
        vec2 dt;
        float addvar = rand*val2;
        dt.x = st.x+sin( st.y*multx + addvar + u_time*3.0)*val3;
        dt.y = st.y+cos( st.x*multy + addvar + u_time*2.4)*val3;
        
        vec4 source = texture2D( u_tex0, dt );
        
        gl_FragColor = source;
    }

); //OFXDOTFRAGSOURCE end

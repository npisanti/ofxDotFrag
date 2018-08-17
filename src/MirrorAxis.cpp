
#include "MirrorAxis.h"

ofx::dotfrag::MirrorAxis::MirrorAxis() {
    name("mirror axis");
    uniform( horizontal.set("horizontal", false), "u_horizontal" );
    uniform( vertical.set("vertical", false), "u_vertical");

    source( code );
}

const std::string ofx::dotfrag::MirrorAxis::code = OFXDOTFRAGSOURCE(

    #ifdef GL_ES
    precision mediump float;
    #endif

    uniform vec2 u_resolution;
    uniform float u_time;
    uniform sampler2D u_tex0;

    uniform bool u_vertical;
    uniform bool u_horizontal;

    void main (void) {
        vec2 st = gl_FragCoord.xy/u_resolution.xy;
        
        if( u_horizontal ){
             st.x = (st.x < 0.5 ) ? 1.0 - st.x : st.x;
        }
        
        if( u_vertical ){
             st.y = (st.y < 0.5) ? 1.0 - st.y : st.y;
        }
        
        vec4 source = texture2D( u_tex0, st );

        gl_FragColor = source;
    }
    
); //OFXDOTFRAGSOURCE end

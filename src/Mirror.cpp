
#include "Mirror.h"

ofx::dotfrag::Mirror::Mirror() {
    name("mirror");
    uniform( horizontal.set("horizontal", false), "u_horizontal" );
    uniform( vertical.set("vertical", false), "u_vertical");

    shader.setupShaderFromSource( GL_VERTEX_SHADER, vertex );
    shader.setupShaderFromSource( GL_FRAGMENT_SHADER, fragment );
    shader.bindDefaults();
    shader.linkProgram();

}

const string ofx::dotfrag::Mirror::vertex = OFXDOTFRAGSOURCE(

#ifdef __ARM_ARCH

    attribute vec4 position;
    attribute vec2 texcoord;
    uniform mat4 modelViewProjectionMatrix;
    varying vec2 texcoord0;
    varying vec2 st;
    uniform bool u_vertical;
    uniform bool u_horizontal;
    
    void main(void){
        gl_Position = modelViewProjectionMatrix * position;
        texcoord0 = texcoord;
        
        st = texcoord0/u_resolution.xy;
        if( u_horizontal ) st.x = 1.0 - st.x;
        if( u_vertical )  st.y = 1.0 - st.y;
    }
    
#else

    varying vec2 texcoord0;
    uniform vec2 u_resolution;
    varying vec2 st;
    uniform bool u_vertical;
    uniform bool u_horizontal;
    
    void main(void){
        texcoord0 = gl_Vertex.xy;
        st = texcoord0/u_resolution.xy;
        
        if( u_horizontal ) st.x = 1.0 - st.x;
        if( u_vertical )  st.y = 1.0 - st.y;
        gl_Position = ftransform();
    }
    
#endif       
    
); //OFXDOTFRAGSOURCE end

const string ofx::dotfrag::Mirror::fragment = OFXDOTFRAGSOURCE(

    #ifdef GL_ES
    precision mediump float;
    #endif

    uniform vec2 u_resolution;
    uniform float u_time;
    uniform sampler2D u_tex0;
    varying vec2 st;

    void main (void) {
        vec4 source = texture2D( u_tex0, st );
        
        gl_FragColor = source;
    }
    
); //OFXDOTFRAGSOURCE end

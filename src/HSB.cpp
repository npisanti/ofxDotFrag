
#include "HSB.h"


ofx::dotfrag::HSB::HSB() {
    name("HSB");
    uniform( hue.set("hue", 0.0f, 0.0f, 1.0f), "u_hue");
    uniform( brightness.set("brightness", 0.0f, -1.0f, 1.0f), "u_brightness");
    uniform( saturation.set("saturation", 1.0f, 0.0f, 2.0f), "u_saturation");
    uniform( contrast.set("contrast", 1.0f, 0.0f, 2.0f), "u_contrast");
    source( code );
}


const string ofx::dotfrag::HSB::code = OFXDOTFRAGSOURCE(

    #ifdef GL_ES
    precision mediump float;
    #endif

    uniform vec2 u_resolution;
    uniform float u_time;
    uniform sampler2D u_tex0;
    varying vec2 st;

    uniform float u_hue;
    uniform float u_saturation;
    uniform float u_brightness;
    uniform float u_contrast;

    //#define TWO_PI 6.28318530718

    vec3 applyHue(vec3 aColor, float aHue)
    {
        float angle = aHue * TWO_PI;
        vec3 k = vec3(0.57735, 0.57735, 0.57735);
        float cosAngle = cos(angle);
        //Rodrigues' rotation formula
        return aColor * cosAngle + cross(k, aColor) * sin(angle) + k * dot(k, aColor) * (1.0 - cosAngle);
    }
     
    void main (void) {

        vec4 source = texture2D( u_tex0, st );
        
        vec3 color = applyHue( source.rgb, u_hue );
        
        color = ((color - 0.5) * u_contrast) + 0.5;
        
        color = color + u_brightness;
        
        vec3 intensity = vec3( dot( color, vec3(0.299,0.587,0.114)) );
        color = mix( intensity, color, u_saturation );

        gl_FragColor = vec4( color, source.a );
    }

); //OFXDOTFRAGSOURCE end

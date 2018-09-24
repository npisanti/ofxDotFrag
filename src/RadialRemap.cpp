
#include "RadialRemap.h"

ofx::dotfrag::RadialRemap::RadialRemap() {
    name("radial remap");

    uniform( angle.set("angle", 0.0f, 0.0f, 1.0f), "u_angle");
    uniform( arc.set("arc", 0.25f, 0.0f, 1.0f), "u_arc");
    uniform( radiusMin.set("radius min", 0.2f, 0.0f, 1.0f), "u_radius_min");
    uniform( radiusMax.set("radius max", 0.45f, 0.0f, 1.0f), "u_radius_max");
    uniform( warp.set("warp", 0.0f, -2.0f, 2.0f), "u_warp");
    uniform( correct.set("correct", 0.2f, 0.0f, 0.5f), "u_correct");
    uniform( flip.set("flip", false), "u_flip");
    
    source( fragment );
}

const std::string ofx::dotfrag::RadialRemap::fragment = OFXDOTFRAGSOURCE(

    // RadialRemap shader
    // Nicola Pisanti ( npisanti.com ) - 2018

    #ifdef GL_ES
    precision mediump float;
    #endif

    uniform vec2 u_resolution;
    uniform float u_time;
    uniform sampler2D u_tex0;
    uniform float u_arc;
    uniform float u_angle;
    uniform float u_radius_min;
    uniform float u_radius_max;
    uniform float u_warp;
    uniform float u_correct;
    uniform float u_flip;

    // ------------------------- functions --------------------------

    const float div_1_pi = 1.0 / 6.28318530717958647692;

    // map input value, clamped to src0--->0.0 and src1--->1.0
    float map01( float value, float src0, float src1 ){ 
        value -= min(src0, src1); 
        value = max( value, 0.0 ); 
        
        float range = src1 - src0; 
        float invert = step( range, 0.0 );
        range = abs(src1 - src0); 
        
        float pct = value / range; 
        
        float invpct = 1.0 - pct;
        return mix( pct, invpct, invert);
    }

    //------------------------------------------------
    float quadratic_correct (float x){
        // adapted from BEZMATH.PS (1993)
        // by Don Lancaster, SYNERGETICS Inc. 
        // http://www.tinaja.com/text/bezmath.html

        // fixed coefficients
        float a = 0.16;
        float b = 1.0 - a;

        // solve t from x (an inverse operation)
        float om2a = 1.0 - 2.0*a;
        float t = (sqrt(a*a + om2a*x) - a)/om2a;
        float y = (1.0-2.0*b)*(t*t) + (2.0*b)*t;
        return y;
    }

    // ----------------------- SHADER CODE --------------------------

    void main(){

        vec2 st = gl_FragCoord.xy/u_resolution.xy;
        
        st -= 0.5;
        
        float angle = atan( st.x, st.y ); 
        float dist = sqrt( dot( st, st ) );

        vec2 radial;
        radial.y = map01(dist, u_radius_min, u_radius_max );
        float gatey = step( 0.01, radial.y) * step( radial.y, 0.98 );
        
        radial.y = mix( 1.0-radial.y, radial.y, u_flip ); // flipped by default
        
        radial.x = angle * div_1_pi;
        radial.x = fract( radial.x + u_angle + radial.y*u_warp );    
        radial.x /= u_arc;

        float amt = quadratic_correct(radial.y) * u_correct;
        radial.x = map01(radial.x, amt, (1.0-amt));
        float gatex = step( 0.01, radial.x) * step( radial.x, 0.98 );    
        
        vec4 source = texture2D( u_tex0, radial );
        source.a *= (gatex*gatey);
        
        gl_FragColor = source;
        
    }


); //OFXDOTFRAGSOURCE end

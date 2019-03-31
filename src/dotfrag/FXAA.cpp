
#include "FXAA.h"

// Implementation of FXAA for GLSL 1.5
// See: https://github.com/mrdoob/three.js/blob/master/examples/js/shaders/FXAAShader.js
//      https://github.com/neilmendoza/ofxPostProcessing/blob/master/src/FxaaPass.cpp
//      http://www.glge.org/demos/fxaa/
//
// Ivaylo Getov
// www.ivaylogetov.com
//
// ported in TheBookOfShader style by Nicola Pisanti, for ofxDotFrag
// https://github.com/npisanti/ofxDotFrag


ofx::dotfrag::FXAA::FXAA() {
    name("fxaa");
    source( code );
}


const std::string ofx::dotfrag::FXAA::code = OFXDOTFRAGSOURCE(

    #ifdef GL_ES
    precision mediump float;
    #endif

    varying vec2 st;
    uniform sampler2D u_tex0;
    uniform vec2 u_resolution;

    const float FXAA_REDUCE_MIN = 1.0/128.0;
    const float FXAA_REDUCE_MUL = 1.0/8.0;
    const float FXAA_SPAN_MAX = 8.0;

    void main() {

        vec2 st = gl_FragCoord.xy/u_resolution;

        vec2 texeldim = vec2(1.0) / u_resolution;
        vec2 v_coord_NW = st + vec2( -1.0, -1.0 ) * texeldim;
        vec2 v_coord_NE = st + vec2(  1.0, -1.0 ) * texeldim;
        vec2 v_coord_SW = st + vec2( -1.0,  1.0 ) * texeldim;
        vec2 v_coord_SE = st + vec2(  1.0,  1.0 ) * texeldim;
        
        vec3 rgbNW = texture2D( u_tex0, v_coord_NW ).xyz;
        vec3 rgbNE = texture2D( u_tex0, v_coord_NE ).xyz;
        vec3 rgbSW = texture2D( u_tex0, v_coord_SW ).xyz;
        vec3 rgbSE = texture2D( u_tex0, v_coord_SE ).xyz;
        vec4 rgbaM = texture2D( u_tex0, st );
        vec3 rgbM  = rgbaM.rgb;
        float opacity  = rgbaM.a;
        
        vec3 luma = vec3( 0.299, 0.587, 0.114 );
        
        float lumaNW = dot( rgbNW, luma );
        float lumaNE = dot( rgbNE, luma );
        float lumaSW = dot( rgbSW, luma );
        float lumaSE = dot( rgbSE, luma );
        float lumaM  = dot( rgbM,  luma );
        float lumaMin = min( lumaM, min( min( lumaNW, lumaNE ), min( lumaSW, lumaSE ) ) );
        float lumaMax = max( lumaM, max( max( lumaNW, lumaNE) , max( lumaSW, lumaSE ) ) );
        
        vec2 dir;
        dir.x = -((lumaNW + lumaNE) - (lumaSW + lumaSE));
        dir.y =  ((lumaNW + lumaSW) - (lumaNE + lumaSE));
        
        float dirReduce = max( ( lumaNW + lumaNE + lumaSW + lumaSE ) * ( 0.25 * FXAA_REDUCE_MUL ), FXAA_REDUCE_MIN );
        
        float rcpDirMin = 1.0 / ( min( abs( dir.x ), abs( dir.y ) ) + dirReduce );

        dir = min( vec2( FXAA_SPAN_MAX*texeldim.x,  FXAA_SPAN_MAX*texeldim.y),
                  max( vec2(-FXAA_SPAN_MAX*texeldim.x, -FXAA_SPAN_MAX*texeldim.y),
                      dir * rcpDirMin)) * u_resolution;
        
        vec3 rgbA = 0.5 * (
                           texture2D( u_tex0, st + dir * (texeldim * ( 1.0 / 3.0 - 0.5 )) ).xyz +
                           texture2D( u_tex0, st + dir * (texeldim * ( 2.0 / 3.0 - 0.5 )) ).xyz );
        
        vec3 rgbB = rgbA * 0.5 + 0.25 * (
                                         texture2D( u_tex0, st + dir * (texeldim * -0.5) ).xyz +
                                         texture2D( u_tex0, st + dir * (texeldim *  0.5) ).xyz );
        
        float lumaB = dot( rgbB, luma );
        
        if ( ( lumaB < lumaMin ) || ( lumaB > lumaMax ) ) {
            gl_FragColor = vec4( rgbA, opacity );
        } else {
            gl_FragColor = vec4( rgbB, opacity );
        }
    }
    
); //OFXDOTFRAGSOURCE end

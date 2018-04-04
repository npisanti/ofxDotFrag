
#pragma once
#include "ofMain.h"

#ifndef OFXDOTFRAGSOURCE
#define OFXDOTFRAGSOURCE(...) OFXDOTFRAGSOURCE_AUX(__VA_ARGS__)
#define OFXDOTFRAGSOURCE_AUX(...) #__VA_ARGS__
#endif

#ifdef __ARM_ARCH
    #ifndef GL_ES
        #define GL_ES
    #endif
#endif


namespace ofx { namespace dotfrag {

class Base {

private: 
    struct UniformPointer;

public:

    Base();

    void allocate( ofFbo & fbo );
    
    // to process an fbo using the shader
    void apply( ofFbo & fbo ); // apply shader to fbo, automatic allocation if fbo size changes

    // those are for drawing shaders that don't process fbos
    void draw( float w, float h ); // draws the shader using 0, 0 as origin
    void draw( float x, float y, float w, float h ); // draws the shader
        
    ofParameterGroup parameters;
        ofParameter<bool>  bActive;
        ofParameter<int>   delay;
        ofParameter<float> speed;
        ofParameter<int>   passes;
        
    void flush(); // clears all the buffers
    void reload(); // reloads the shader
    
    void stop();    
    void pause();
    void play( float speed=1.0f );


protected:

    void name( string value );

    void framebuffer( int maxdelay ); // delay buffer, delay is in u_tex1
    void pingpong(); // ping pong buffer using u_tex1 for old frame
    void timewarp(); // add controls for playback speed of u_time
    void multipass( int maxpasses ); // repeat the same process again

    void uniform( ofParameter<float> & param );
    void uniform( ofParameter<int> & param );
    void uniform( ofParameter<bool> & param );
    void uniform( ofParameter<ofColor> & param );
    
    void uniform( ofParameter<float> & param, std::string uniformName );
    void uniform( ofParameter<int> & param, std::string uniformName  );
    void uniform( ofParameter<bool> & param, std::string uniformName  );
    void uniform( ofParameter<ofColor> & param, std::string uniformName  );

    void load ( std::string path );
    void source( std::string sourcestring );

    // to be overloaded for calculating additional uniforms
    virtual void preshading( float w, float h ) {}; 
    
    // direct acces to shader
    ofShader        shader;

private:
    void updateUniforms( float w, float h );

    void buffersize( int num ); 
    void update( ofFbo & fbo ); // update, use for processing fbos
    void update( float w, float h ); // update for graphic shaders
    void draw( ofFbo & fbo  );


    unsigned int    bIndex;
    std::vector<ofFbo>  	buffers;

    static int      constructed;

    std::vector<UniformPointer> uniforms;

    float before;
    float clock;

    static const float cMult;
    bool bTimeWarp;

    bool bDelay;
    std::string path;
    std::string fullname;
    std::stringstream vertexSrc;
    
    struct UniformPointer{
        UniformPointer(){
            type = -1;
            name = "";
            fp = nullptr;
            cp = nullptr;
            ip = nullptr;
            cp = nullptr;
        }
        int type;
        std::string name;
        ofParameter<float> *    fp;
        ofParameter<int> *      ip;
        ofParameter<bool> *     bp;
        ofParameter<ofColor> *  cp;
    };

};

}} // end namespaces

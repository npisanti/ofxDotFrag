
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

    // you don't need this if you don't use apply() 
    // or ping pong buffers
    void allocate( ofFbo & fbo ); 
    void allocate( int w, int h );

    // to process an fbo using the shader
    // automatic allocation if fbo size changes
    void apply( ofFbo & fbo ); 

    // draw shader to fbo, clearing it before
    // also allocation is not needed
    void drawTo( ofFbo & fbo ); 


    ofParameterGroup parameters;
        ofParameter<bool>  active;
        ofParameter<int>   delay; // num of delay frames
        ofParameter<float> speed;
        ofParameter<int>   passes;

    void flush(); // clears all the buffers
    void reload(); // reloads the shader

    void stop();
    void pause();
    void play( float speed=1.0f );
    void setTime( float value ){ clock = value; }

    const std::string & path() const;

    void name( string value );

    void framebuffer( int maxdelay ); // delay buffer, delay is in u_tex1
    void pingpong(); // ping pong buffer using u_tex1 for old frame
    void timewarp(); // add controls for playback speed of u_time
    void multipass( int maxpasses ); // repeat the same process again

    void uniform( ofParameter<float> & param );
    void uniform( ofParameter<int> & param );
    void uniform( ofParameter<bool> & param );
    void uniform( ofParameter<ofColor> & param );
    void uniform( ofParameter<glm::vec2> & param );
    void uniform( ofParameter<glm::vec3> & param );
    void uniform( ofParameter<glm::vec4> & param );

    void uniform( ofParameter<float> & param, std::string uniformName, bool addToParameters=true );
    void uniform( ofParameter<int> & param, std::string uniformName, bool addToParameters=true );
    void uniform( ofParameter<bool> & param, std::string uniformName, bool addToParameters=true );
    void uniform( ofParameter<ofColor> & param, std::string uniformName, bool addToParameters=true );
    void uniform( ofParameter<glm::vec2> & param, std::string uniformName, bool addToParameters=true );
    void uniform( ofParameter<glm::vec3> & param, std::string uniformName, bool addToParameters=true );
    void uniform( ofParameter<glm::vec4> & param, std::string uniformName, bool addToParameters=true );

    virtual void load ( std::string filepath );
    void source( std::string sourcestring );

    ofParameterGroup & label( std::string name );

protected:
    // to be overloaded for calculating additional uniforms
    virtual void preshading( float w, float h ) {};
    
    // access to shader
    ofShader        shader;
    
    std::string filepath;

private:
    void updateUniforms( float w, float h );

    void buffersize( int num );
    void update( ofFbo & fbo ); // update, use for processing fbos
    void draw( ofFbo & fbo  );

    void render( float w, float h );

    unsigned int    bIndex;
    std::vector<ofFbo>  	buffers;

    static int      constructed;

    std::vector<UniformPointer> uniforms;

    float before;
    float clock;

    static const float cMult;
    bool bTimeWarp;

    bool bDelay;

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
            v2p = nullptr;
            v3p = nullptr;
            v4p = nullptr;
        }
        int type;
        std::string name;
        ofParameter<float> *    fp;
        ofParameter<int> *      ip;
        ofParameter<bool> *     bp;
        ofParameter<ofColor> *  cp;
        ofParameter<glm::vec2> *  v2p;
        ofParameter<glm::vec3> *  v3p;
        ofParameter<glm::vec4> *  v4p;
    };

};

}} // end namespaces

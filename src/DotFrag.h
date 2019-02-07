
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

    void allocate( ofFbo & fbo ); // you don't need this if you don't use apply()

    void allocate( int w, int h );

    // to process an fbo using the shader
    void apply( ofFbo & fbo ); // apply shader to fbo, automatic allocation if fbo size changes

    void drawTo( ofFbo & fbo ); // draw shader to fbo, clearing it before

    // just draws the shader without using internal fbo, you don't need to allocate()
    void draw( float x, float y, float w, float h );


    // use those to draw with your own primitives
    void begin( int w, int h );
    void end();

    ofParameterGroup parameters;
        ofParameter<bool>  active;
        ofParameter<int>   delay;
        ofParameter<float> speed;
        ofParameter<int>   passes;

    void flush(); // clears all the buffers
    void reload(); // reloads the shader

    void stop();
    void pause();
    void play( float speed=1.0f );

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

    void uniform( ofParameter<float> & param, std::string uniformName );
    void uniform( ofParameter<int> & param, std::string uniformName  );
    void uniform( ofParameter<bool> & param, std::string uniformName  );
    void uniform( ofParameter<ofColor> & param, std::string uniformName  );
    void uniform( ofParameter<glm::vec2> & param, std::string uniformName   );
    void uniform( ofParameter<glm::vec3> & param, std::string uniformName   );
    void uniform( ofParameter<glm::vec4> & param, std::string uniformName   );

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

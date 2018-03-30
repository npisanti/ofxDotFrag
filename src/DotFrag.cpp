
#include "DotFrag.h"

int ofx::dotfrag::Base::constructed = 0;
const float ofx::dotfrag::Base::cMult = 1.0f / 255.0f;

ofx::dotfrag::Base::Base() {

    vertexSrc.str(std::string());
#ifdef __ARM_ARCH
    vertexSrc  << "attribute vec4 position;\n";
    vertexSrc  << "attribute vec2 texcoord;\n";
    vertexSrc  << "uniform vec2 u_resolution;\n";
    vertexSrc  << "varying vec2 st;\n";
    vertexSrc  << "uniform mat4 modelViewProjectionMatrix;\n";
    vertexSrc  << "varying vec2 texcoord0;\n";
    vertexSrc  << "void main(void){\n";
    vertexSrc  << "\tgl_Position = modelViewProjectionMatrix * position;\n";
    vertexSrc  << "\ttexcoord0 = texcoord;\n";
    vertexSrc  << "\tst = texcoord0/u_resolution.xy;\n";
    vertexSrc  << "}\n";
#else
    vertexSrc  << "varying vec2 texcoord0;\n";
    vertexSrc  << "uniform vec2 u_resolution;\n";
    vertexSrc  << "varying vec2 st;\n";
    vertexSrc  << "void main(void){\n";
    vertexSrc  << "\ttexcoord0 = gl_Vertex.xy;\n";
    vertexSrc  << "\tst = texcoord0/u_resolution.xy;\n";
    vertexSrc  << "\tgl_Position = ftransform();\n";
    vertexSrc  << "}\n";
#endif       

    bIndex = 0;
    bDelay = false;
    buffers.resize(1);

    delay = 0;
    
    passes = 1;

    uniforms.reserve(12);

    ofDisableArbTex();
    if(constructed==0) ofLogNotice()<<"[ofx::dotfrag::Base] disabling ARB textures for shaders\n";
    constructed++;

    fullname = ".frag";
    parameters.setName( fullname );
    parameters.add( bActive.set("active", true) );

    bTimeWarp = false;
    
    clock = 0.0f;
    before = 0.0f;
    path = "";
}

void ofx::dotfrag::Base::updateUniforms( float w, float h ){
    
    if( bTimeWarp ){            
        float now = ofGetElapsedTimef();
        clock += (now-before) * (speed*speed*speed);
        before = now;
        shader.setUniform1f( "u_time", clock ); 
    }else{
        shader.setUniform1f( "u_time", ofGetElapsedTimef() );
    }

    shader.setUniform2f( "u_resolution", w, h );
    
    for( size_t i=0; i<uniforms.size(); ++i ){
        switch( uniforms[i].type ){
            case 0:
                shader.setUniform1f( uniforms[i].name, *(uniforms[i].fp) );
            break;
            
            case 1:
                shader.setUniform1i( uniforms[i].name, *(uniforms[i].ip) );
            break;
            
            case 2:
                shader.setUniform1i( uniforms[i].name, *(uniforms[i].bp) );
            break;
            
            case 3:
                shader.setUniform3f(uniforms[i].name, uniforms[i].cp->get().r*cMult, uniforms[i].cp->get().g*cMult, uniforms[i].cp->get().b*cMult );
            break;
        }
    }
}

void ofx::dotfrag::Base::buffersize( int num ) {
    buffers.resize( num );
    if( num==2 ){
        delay = 1;
        bDelay = true;
    }else if( num>2){
        parameters.add( delay.set("delay", 1, 1, num-1) );
        bDelay = true;
    } 
}

void ofx::dotfrag::Base::pingpong(){
    buffersize(2);
}

void ofx::dotfrag::Base::framebuffer( int maxdelay ){
    buffersize( maxdelay+1 );
}

void ofx::dotfrag::Base::name( string value ) {
    fullname = value;
    parameters.setName( fullname );
}

void ofx::dotfrag::Base::timewarp(){
    parameters.add( speed.set("speed", 1.0f, 0.0f, 2.0f) );
    bTimeWarp = true;
}

void ofx::dotfrag::Base::multipass( int maxpasses ){
    parameters.add( passes.set("passes", 1, 1, maxpasses) );
}

void ofx::dotfrag::Base::uniform( ofParameter<float> & param, string uniformName ){
    parameters.add( param );
    uniforms.emplace_back();
    uniforms.back().name = uniformName;
    uniforms.back().type = 0;
    uniforms.back().fp = &param;
}

void ofx::dotfrag::Base::uniform( ofParameter<int> & param, string uniformName ){
    parameters.add( param );
    uniforms.emplace_back();
    uniforms.back().name = uniformName;
    uniforms.back().type = 1;
    uniforms.back().ip = &param;
}

void ofx::dotfrag::Base::uniform( ofParameter<bool> & param, string uniformName ){
    parameters.add( param );
    uniforms.emplace_back();
    uniforms.back().name = uniformName;
    uniforms.back().type = 2;
    uniforms.back().bp = &param;
}

void ofx::dotfrag::Base::uniform( ofParameter<ofColor> & param, string uniformName  ){
    parameters.add( param );
    uniforms.emplace_back();
    uniforms.back().name = uniformName;
    uniforms.back().type = 3;
    uniforms.back().cp = &param;
}

void ofx::dotfrag::Base::uniform( ofParameter<float> & param ){
    uniform( param, param.getName() );
}

void ofx::dotfrag::Base::uniform( ofParameter<bool> & param ){
    uniform( param, param.getName() );
}

void ofx::dotfrag::Base::uniform( ofParameter<int> & param ){
    uniform( param, param.getName() );
}

void ofx::dotfrag::Base::uniform( ofParameter<ofColor> & param ){
    uniform( param, param.getName() );
}

void ofx::dotfrag::Base::load ( string path ){
    this->path = path;
    reload();
}

void ofx::dotfrag::Base::reload(){
    if( path!="" ){
        shader.setupShaderFromSource( GL_VERTEX_SHADER, vertexSrc.str() );
        shader.setupShaderFromFile( GL_FRAGMENT_SHADER, path );
        shader.bindDefaults();
        shader.linkProgram();
    }
}

void ofx::dotfrag::Base::source( string sourcestring ){
    shader.setupShaderFromSource( GL_VERTEX_SHADER, vertexSrc.str() );
    shader.setupShaderFromSource( GL_FRAGMENT_SHADER, sourcestring );
    shader.bindDefaults();
    shader.linkProgram();
}

void ofx::dotfrag::Base::stop(){
    speed = 0.0f;
    clock = 0.0f;
}

void ofx::dotfrag::Base::pause(){
    speed = 0.0f;
}

void ofx::dotfrag::Base::play( float speed ){
    this->speed = speed;
}

void ofx::dotfrag::Base::update( ofFbo & fbo ) {
    
    allocate( fbo );

    buffers[bIndex].begin();
        ofClear(0,0,0,0);
        if(bActive){
            draw( fbo );
        }else{
            fbo.draw(0,0);
        }
    buffers[bIndex].end();

    if(bDelay){
        bIndex++;
        if(bIndex>=buffers.size()) bIndex = 0;
    }
}

void ofx::dotfrag::Base::draw( ofFbo & fbo  ){
    shader.begin();
    preshading( fbo.getWidth(), fbo.getHeight() );
    updateUniforms( fbo.getWidth(), fbo.getHeight() );
    shader.setUniformTexture("u_tex0", fbo.getTexture(), fbo.getTexture().getTextureData().textureID );
    if(bDelay){
        int dIndex = bIndex - delay;
        if( dIndex < 0 ) dIndex += buffers.size();
        shader.setUniformTexture("u_tex1", buffers[dIndex].getTexture(), buffers[dIndex].getTexture().getTextureData().textureID );
    }
    ofSetColor(255, 255, 255, 255);
    ofDrawRectangle(0, 0, fbo.getWidth(), fbo.getHeight() );
    shader.end();
}

void ofx::dotfrag::Base::apply( ofFbo & fbo ){
    if(bActive){
        for( int i=0; i<passes; ++i){ // there is shurely a faster way to do this
            update( fbo );            

            fbo.begin();
                ofClear(0,0,0,0);
                ofSetColor(255, 255, 255, 255);
                int now = bIndex-1;
                if(now<0) now+=buffers.size();
                buffers[now].draw(0,0);
            fbo.end();
        }
    }
}

void ofx::dotfrag::Base::allocate( ofFbo & fbo ) {
    for(size_t i=0; i<buffers.size(); ++i ){
        if( buffers[i].getWidth()!=fbo.getWidth() || buffers[i].getHeight()!=fbo.getHeight() ){
            buffers[i].allocate( fbo.getWidth(), fbo.getHeight() );
            buffers[i].begin();
                ofClear(0, 0, 0, 0);
            buffers[i].end();
            ofLogVerbose() <<"["<<fullname<<"] allocating buffer "<<i<<"\n";
        }
    }
}

void ofx::dotfrag::Base::flush(){
    for(size_t i=0; i<buffers.size(); ++i ){
        buffers[i].begin();
            ofClear( 0, 0, 0, 0 );
        buffers[i].end();
    }
}

// ------------------------- NON-FILTER ---------------------------------------

void ofx::dotfrag::Base::update( float w, float h ){

    for(size_t i=0; i<buffers.size(); ++i ){
        if(buffers[bIndex].getWidth()!=w || buffers[bIndex].getHeight()!=h){
            buffers[i].allocate( w, h );
            buffers[i].begin();
                ofClear(0, 0, 0, 0);
            buffers[i].end();
            ofLogVerbose()<<"["<<fullname<<"] reallocating buffer";
        }
    } 

    buffers[bIndex].begin();
        ofClear(0,0,0,0);
        draw( w, h );
    buffers[bIndex].end();
    }


void ofx::dotfrag::Base::draw( float w, float h ){
    if(bActive){
        shader.begin();
        preshading( w, h );
        updateUniforms( w, h );
        ofDrawRectangle(0, 0, w, h);
        shader.end();        
    }
}

void ofx::dotfrag::Base::draw( float x, float y, float w, float h ){
    ofPushMatrix();
        ofTranslate( x, y );
        draw( w, h );
    ofPopMatrix();
}

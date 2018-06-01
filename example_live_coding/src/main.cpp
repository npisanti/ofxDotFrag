#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

#ifdef __ARM_ARCH
    ofGLESWindowSettings settings;
    settings.glesVersion = 2;
    settings.setSize( 640, 640 );
    ofCreateWindow(settings); 
#else        
	ofSetupOpenGL( 640, 640, OF_WINDOW);			// <-------- setup the GL context
#endif
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofApp());

}

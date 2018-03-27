
#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main(int argc, char *argv[]){

#ifdef __ARM_ARCH
    ofGLESWindowSettings settings;
    settings.glesVersion = 2;
    settings.width = 640;
    settings.height = 700;
    ofCreateWindow(settings);
#else        
    ofSetupOpenGL(640, 700, OF_WINDOW);	        
#endif

	ofApp *app = new ofApp();
	app->arguments = vector<string>(argv, argv + argc);
    ofRunApp( app );

}

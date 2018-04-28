#pragma once

#include "ofMain.h"

#include "ofxGui.h"
#include "ofxDotFrag.h"
#include "ofxWatchFile.h"


class LiveShader : public ofx::dotfrag::Base {
    
public:
    ofParameter<float> var0;
    ofParameter<float> var1;

    LiveShader(){
        name( "live shader" );
        uniform( var0.set("u_var0", 0.5f, 0.0f, 1.0f) );
        uniform( var1.set("u_var1", 0.5f, 0.0f, 1.0f) );
        load( "live.frag" );
    }

};


class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        
        bool bDrawGui;
        ofxPanel gui;
        LiveShader frag;
        
        ofxWatchFile watcher;
        void onFileChange( ofFile &file );
        
};

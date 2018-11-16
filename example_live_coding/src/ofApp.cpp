#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("live shader");
    bDrawGui = true;

    frag.name( "live shader" );
    frag.uniform( var0.set("u_var0", 0.5f, 0.0f, 1.0f) );
    frag.uniform( var1.set("u_var1", 0.5f, 0.0f, 1.0f) );
    frag.load( "live.frag" );

    //frag.load( "live.frag", false ); // you can also load without watching for file changes

    gui.setup("", "settings.xml", 20, 20 );
    gui.setName("press g to close");
    gui.add( frag.parameters );

    fbo.allocate( 640, 480 );
    frag.allocate( fbo );

    mode = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    switch (mode){
        case 0:  break;

        case 1:
            if( vidGrabber.isInitialized()){
                vidGrabber.update();
                if(vidGrabber.isFrameNew()){
                    fbo.begin();
                        ofClear(0,0,0,0);
                        vidGrabber.draw( 0, 0 );
                    fbo.end();
                    frag.apply( fbo );
                }
            }else{
                if(!bCamOpen){
                    openCam();
                    bCamOpen = true;
                }
            }
        break;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(0);

    switch (mode){
        case 0:
            ofSetColor( 255, 0, 0 );
            frag.draw( 0, 0, ofGetWidth(), ofGetHeight() );
        break;

        default: fbo.draw( 0, 0 ); break;
    }

    if(bDrawGui) gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    switch( key ){
        case '0': mode = 0; break;
        case '1': mode = 1; break;
		case '2': mode = 2; break;
		case '3': mode = 3; break;
        case 'g': bDrawGui = !bDrawGui; break;
    }
}

void ofApp::openCam(){
    vidGrabber.setDeviceID( 0 );
    vidGrabber.setDesiredFrameRate(60);
    vidGrabber.initGrabber(640, 480);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

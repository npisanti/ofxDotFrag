#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("live shader");
    bDrawGui = true;
    
    watcher.setCheckIntervalTimef( 0.03f );
    watcher.addListener(this, &ofApp::onFileChange);
	watcher.setTargetPath( frag.path() );
    
    gui.setup("", "settings.xml", 20, 20 );
    gui.setName("press g to close");
    gui.add( frag.parameters );
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    frag.draw( ofGetWidth(), ofGetHeight() );
    if(bDrawGui) gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key=='r' ) frag.reload();
    if( key=='g' ) bDrawGui = !bDrawGui;
}

void ofApp::onFileChange( ofFile &file ){
    frag.reload();
    ofLogNotice() << "fragment shader reloaded";
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

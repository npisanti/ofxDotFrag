#include "ofApp.h"

// change the name of the shader in ofApp.h to test different shaders

// scope.png from wikipedia

//--------------------------------------------------------------
void ofApp::setup(){

    //ofSetLogLevel( OF_LOG_VERBOSE );

    img.load( "scope.png");

    fbo.allocate( 640, 480 );

    mode = 3;
    nCursor = ofRandom(1.0f);

    frag.allocate( fbo );

    bCamOpen = false;

    ofBackground(0);

    bDrawGui = true;
    bDisplayFps = true;

    gui.setup( "", "setting.xml", 20, 500 );
    gui.setName( "GUI" );
    gui.add( frag.parameters );

}

void ofApp::openCam(){
    vidGrabber.setDeviceID( 0 );
    vidGrabber.setDesiredFrameRate(60);
    vidGrabber.initGrabber(640, 480);
}
		
void ofApp::windowResized(int w, int h){
	if( bDrawGui ){
		fbo.allocate( ofGetWidth(), ofGetHeight()-220 );
		gui.setPosition(20, ofGetHeight()-200 );
	}else{
		fbo.allocate( ofGetWidth(), ofGetHeight() );
	}

}

//--------------------------------------------------------------
void ofApp::update(){

    switch (mode) {

        case 1:
        {
            fbo.begin();
                ofClear(0,0,0,0);
                ofSetLineWidth(3.0f);

                static const float nOffset = 0.3f;
                static const int points = 3;
                nCursor += 0.0007;
                
                ofFill();
                ofSetColor(255);
                for( int k=0; k<3; ++k){
                    /*
                    switch( k ){
                        case 0: ofSetColor( 255, 0, 0, 245 ); break;
                        case 1: ofSetColor( 0, 255, 0, 245 ); break;
                        case 2: ofSetColor( 0, 0, 255, 245 ); break;
                    }
                    */ 
                    ofBeginShape();
                    for(int i=0; i<points; ++i){
                        int x = ofNoise((k*points+i)*nOffset, nCursor)*fbo.getWidth();
                        int y = ofNoise((k*points+i)*2.0f*nOffset, nCursor)*fbo.getHeight();
                        ofVertex( x, y );
                    }
                    ofEndShape(true);
                }
                /*
                ofNoFill();
                ofSetColor(255);
                for( int k=0; k<3; ++k){
                    ofBeginShape();
                    for(int i=0; i<points; ++i){
                        int x = ofNoise((k*points+i)*nOffset, nCursor)*fbo.getWidth();
                        int y = ofNoise((k*points+i)*2.0f*nOffset, nCursor)*fbo.getHeight();
                        ofDrawBitmapString("vertex " + ofToString(i), x, y );
                        ofVertex( x, y );
                    }
                    ofEndShape(true);
                }
                */ 
            fbo.end();
            frag.apply( fbo );
        }
        break;
        
        case 2:
            fbo.begin();
                ofClear(0,0,0,0);
                img.draw(0,0);
            fbo.end();
            frag.apply( fbo );
        break;
        
        case 3:
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
	fbo.draw( 0, 0 );
	//frag.draw( 0, 0 );
	if(bDrawGui) gui.draw();
	ofSetColor(255);
	if(bDisplayFps) ofDrawBitmapString( "fps="+ofToString(ofGetFrameRate()), 20, 20 );

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch( key ){
		case '1': mode = 1; break;
		case '2': mode = 2; break;
		case '3': mode = 3; break;
		case '4': mode = 4; break;
		case '5': mode = 5; break;
		case '0': mode = 0; break;
		case 'g': bDrawGui = !bDrawGui;	break;
		case ' ': frag.bActive = true; break;
		case 'r': frag.reload(); break;
		case 'f': bDisplayFps = !bDisplayFps; break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if( key == ' ' ) frag.bActive = false;
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
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

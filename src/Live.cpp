
#include "Live.h"

ofx::dotfrag::Live::Live(){
    interval = 0.05f;
    timePassed = 0.0f;
}

void ofx::dotfrag::Live::load( std::string path ) {
    load ( path, true );
}

void ofx::dotfrag::Live::load( std::string path, bool watch ) {
    filepath = path;

    if( ! ofFilePath::isAbsolute( filepath )){
        filepath = ofToDataPath( filepath );
    }

    ofFile file( filepath );
    if( file.exists() ){
        if( watch ){
            ofAddListener(ofEvents().update, this, &Live::update);
            writeTimestamp = boost::filesystem::last_write_time( filepath );
        }
        reload();
    }else{
        ofLogError() << "[ofx::dotfrag::Live] file to load does not exists\n";
    }
}

void ofx::dotfrag::Live::update(ofEventArgs &args){
    timePassed += ofGetLastFrameTime();
    if( timePassed > interval ){
        time_t checkTimestamp = boost::filesystem::last_write_time( filepath );
        if( checkTimestamp != writeTimestamp){
            writeTimestamp = checkTimestamp;
            reload();
            ofLogNotice() << "["<<filepath<<"] shader reloaded";
        }
    }
}


#pragma once

#include "Base.h"

// Twist shader, ported from ofxPostGlitch
// https://github.com/maxillacult/ofxPostGlitch.git

namespace ofx { namespace dotfrag {

class Twist : public Base {

private:
    static const std::string fragment;

    void preshading( float w, float h ) override;

public:
	Twist();
    
    ofParameter<float> amount;
	ofParameter<float> variation;
};

}} // namespaces end

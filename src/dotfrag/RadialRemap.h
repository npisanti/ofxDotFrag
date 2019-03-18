
#pragma once

#include "Base.h"

namespace ofx { namespace dotfrag {

class RadialRemap : public Base {

private:
    static const std::string fragment;

public:
	RadialRemap();
    
	ofParameter<float> angle;
	ofParameter<float> arc;

	ofParameter<float> radiusMin;
	ofParameter<float> radiusMax;
    
	ofParameter<float> warp;
	ofParameter<float> correct;
    
    ofParameter<bool> flip;
    
};

}} // namespaces end

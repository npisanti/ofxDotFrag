
#pragma once

#include "Base.h"

namespace ofx { namespace dotfrag {

class ThreeTones : public Base {

private: 
    static const std::string code;

public:
	ThreeTones();

    ofParameter<float> mix;
	ofParameter<float> fade;
    vector<ofParameter<float>> thresholds;
    vector<ofParameter<ofColor>> colors;

};

}} // namespaces end

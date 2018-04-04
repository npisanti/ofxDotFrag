
#pragma once

#include "DotFrag.h"

namespace ofx { namespace dotfrag {

class Turbolence : public Base {

private:
    static const std::string code;

public:
	Turbolence();
    
    ofParameter<float> x;
	ofParameter<float> y;
};

}} // namespaces end

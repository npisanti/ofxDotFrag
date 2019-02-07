
#pragma once

#include "DotFrag.h"

namespace ofx { namespace dotfrag {

class Monochrome : public Base {

private:
    static const std::string code;

public:
	Monochrome();
    
    ofParameter<float> low;
    ofParameter<float> high;
    
};

}} // namespaces end

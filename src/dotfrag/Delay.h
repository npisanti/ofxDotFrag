
#pragma once

#include "Base.h"

namespace ofx { namespace dotfrag {

class Delay : public Base {

private:
    static const std::string code;
    
public:
    Delay();
    
    ofParameter<float> feedback;
    ofParameter<int>   blendmode;
    
};

}} // end namespaces


#pragma once

#include "Base.h"

namespace ofx { namespace dotfrag {

class Mirror : public Base {

private:
    static const std::string code;

public:
	Mirror();
    
    ofParameter<bool> horizontal;
	ofParameter<bool> vertical;
};

}} // namespaces end


#pragma once

#include "Base.h"

namespace ofx { namespace dotfrag {

class MirrorAxis : public Base {

private:
    static const std::string code;

public:
	MirrorAxis();
    
    ofParameter<bool> horizontal;
	ofParameter<bool> vertical;
};

}} // namespaces end

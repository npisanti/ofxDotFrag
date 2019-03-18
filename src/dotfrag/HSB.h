
#pragma once

#include "Base.h"

namespace ofx { namespace dotfrag {

class HSB : public Base {

private:
    static const std::string code;

public:
	ofParameter<float> hue;
	ofParameter<float> brightness;
	ofParameter<float> saturation;
	ofParameter<float> contrast;

	HSB();
};

}} // end namespaces

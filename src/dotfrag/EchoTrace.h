
#pragma once

#include "Base.h"

namespace ofx { namespace dotfrag {

class EchoTrace : public Base {

private:
    static const std::string code;

public:
	EchoTrace();
    
	ofParameter<float> gain;
	ofParameter<float> threshold;
	ofParameter<bool> invert;
	ofParameter<bool> hardCutoff;
};

}} // namespaces end

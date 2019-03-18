#pragma once

#include "Base.h"
#include <boost/filesystem.hpp>

namespace ofx { namespace dotfrag {

class Live : public Base {

public:
	Live();

    void load( std::string path ) override;
    void load( std::string path, bool watch );

    float interval;

private:
    time_t writeTimestamp;
    float timePassed;
    void update(ofEventArgs &args);
};

}} // namespaces end

/**
 * @file track.cpp
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "track.hpp"

#include <string>

struct Track::Impl {

    std::string title;
    std::string codec;
    unsigned int duration;
};

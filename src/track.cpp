/**
 * @file track.cpp
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "track.hpp"

#include <string>
#include <fstream>

struct Track::Impl {

    std::string title;
    std::string codec;
    unsigned int duration;
};

/**
 *
 */
Track::Track(const std::string& filename) : impl(std::make_unique<Impl>()) {

    std::ifstream file(filename);

    /* FIXME: check what to do in case of error when opening the file */

    getline(
        file,
        impl->title,
        '\n'
    );

    getline(
        file,
        impl->codec,
        '\n'
    );

    /* FIXME: read duration and content */
}

/**
 *
 */
Track::~Track() = default;

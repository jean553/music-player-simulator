/**
 * @file track.cpp
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "track.hpp"

#include <string>

struct Track::Impl {

    std::string title;
    std::string codec;

    unsigned int duration {0};
    unsigned int position {0};
};

/**
 *
 */
Track::Track(
    const std::string title,
    const std::string codec
) : impl(std::make_unique<Impl>()) {
    impl->title = title;
    impl->codec = codec;
}

/**
 *
 */
Track::Track(const Track& track) : impl(std::make_unique<Impl>()) {

    impl->title = track.impl->title;
    impl->codec = track.impl->codec;
}

/**
 *
 */
Track::Track(Track&& track) : impl(std::move(track.impl)) {
}

/**
 *
 */
Track::~Track() = default;

/**
 *
 */
const std::string& Track::getTitle() const & noexcept {
    
    return impl->title;
}

/**
 *
 */
const unsigned int& Track::getPosition() const & noexcept {

    return impl->position;
}

/**
 *
 */
void Track::incrementPosition() const & noexcept {

    impl->position += 1;
}

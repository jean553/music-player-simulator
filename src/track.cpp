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
    unsigned int position {0};

    bool playing {true};
};

/**
 *
 */
Track::Track(
    const std::string title,
    const std::string codec,
    const unsigned int duration
) :
    impl(std::make_unique<Impl>()) {

    impl->title = title;
    impl->codec = codec;
    impl->duration = duration;
}

/**
 *
 */
Track::Track(const Track& track) : impl(std::make_unique<Impl>()) {

    const auto& source = track.impl;
    impl->title = source->title;
    impl->codec = source->codec;
    impl->duration = source->duration;
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
const std::string& Track::getCodec() const & noexcept {

    return impl->codec;
}

/**
 *
 */
const unsigned int& Track::getDuration() const & noexcept {

    return impl->duration;
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
void Track::pause() const & noexcept {

    impl->playing = false;
}

/**
 *
 */
void Track::incrementPosition() const & noexcept {

    impl->position += 1;
}

/**
 *
 */
const bool& Track::isPlaying() const & noexcept {

    return impl->playing;
}

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
    unsigned int position;

    bool playing;
    bool repeat;
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
    impl->position = 0;
    impl->playing = true;
    impl->repeat = false;
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
void Track::resume() const & noexcept {

    impl->playing = true;
}

/**
 *
 */
void Track::restart() const & noexcept {

    impl->position = 0;
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

/**
 *
 */
const bool& Track::isRepeated() const & noexcept {

    return impl->repeat;
}

/**
 *
 */
void Track::repeat() const & noexcept {

    impl->repeat = true;
}

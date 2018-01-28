/**
 * @file track.hpp
 * @brief track structure definition
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef TRACK_H_
#define TRACK_H_

#include <memory>

struct Track {

    /**
     * @brief constructs a track from the given parameters
     *
     * @param title the title of the track
     * @param codec the codec of the track
     * @param duration the track duration
     *
     * expensive strings copies occure here,
     * we cannot simply use references
     * as this data is supposed to be loaded from a file
     * into a dedicated function
     *
     * TODO: expensive copies, should be improved
     */
    Track(
        const std::string title,
        const std::string codec,
        const unsigned int duration
    );

    /**
     * @brief default destructor required for separated implementation
     */
    ~Track();

    /**
     * @brief getter of the track title
     *
     * @return const std::string&
     */
    const std::string& getTitle() const & noexcept;

    /**
     * @brief getter of the track codec
     *
     * @return const std::string&
     */
    const std::string& getCodec() const & noexcept;

    /**
     * @brief getter of the track duration
     *
     * @return const unsigned int&
     */
    const unsigned int& getDuration() const & noexcept;

    /**
     * @brief getter of the current track position
     *
     * @return const unsigned int&
     */
    const unsigned int& getPosition() const & noexcept;

    /**
     * @brief increments the track position when playing
     */
    void incrementPosition() const & noexcept;

    /**
     * @brief pauses the playing track, set playing boolean to false
     */
    void pause() const & noexcept;

    /**
     * @brief resumes the current paused track, set playing boolean to true
     */
    void resume() const & noexcept;

    /**
     * @brief restarts the current track, used for repetition
     * and at the end of playing
     */
    void restart() const & noexcept;

    /**
     * @brief indicates if the track is playing
     *
     * @return const bool&
     */
    const bool& isPlaying() const & noexcept;

    struct Impl;
    std::unique_ptr<Impl> impl;
};

#endif

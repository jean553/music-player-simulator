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
        const std::string codec
    );

    /**
     * @brief default destructor required for separated implementation
     */
    ~Track();

    /**
     * @brief copy constructor that ensures copy of the implementation content
     * referenced by a brand new unique pointer; used when copied the track
     * into the playing thread
     *
     * @param track the source track
     */
    Track(const Track& track);

    /**
     * @brief move constructor in order to automatically remove
     * all the copy operations and ensure implementation
     * unique pointer movement
     */
    Track(Track&& track);

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
     * @brief getter of the current track position
     *
     * @return const unsigned int&
     */
    const unsigned int& getPosition() const & noexcept;

    /**
     * @brief increments the track position when playing
     */
    void incrementPosition() const & noexcept;

    struct Impl;
    std::unique_ptr<Impl> impl;
};

#endif

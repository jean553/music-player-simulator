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

    struct Impl;
    const std::unique_ptr<Impl> impl;
};

#endif

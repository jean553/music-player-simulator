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
     * @brief constructs a track from the given file
     */
    Track(const std::string& filename);

    /**
     * @brief default destructor required for separated implementation
     */
    ~Track();

    struct Impl;
    const std::unique_ptr<Impl> impl;
};

#endif

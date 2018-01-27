/**
 * @file playlist.cpp
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "playlist.hpp"
#include "track.hpp"

#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <fstream>

/**
 *
 */
void listAllTracks(const std::vector<std::string>& playlist) {

    std::for_each(
        playlist.cbegin(),
        playlist.cend(),
        [](const std::string& item) {
            std::cout << item << std::endl;
        }
    );
}

/**
 *
 */
void removeDuplicates(std::vector<std::string>& playlist) {

    /* tries to insert every item one by one into an unordered set
       (unordered only for performance purposes);
       check if the insertion has failed (item already there),
       then simply remove the item from the playlist */

    std::unordered_set<std::string> temporarySet;

    /* use a basic for loop with an index instead of a more modern
       way to iterate because manipulating the index during
       an iteration is required in this case */

    for (
        auto index = 0u;
        index < playlist.size();
        index += 1
    ) {

        if (temporarySet.insert(playlist[index]).second) {
            continue;
        }

        playlist.erase(playlist.begin() + index);
        index -= 1;
    }
}

/**
 *
 */
void removeTrack(
    std::vector<std::string>& playlist,
    const std::string& track
) {

    const auto index = std::find(
        playlist.cbegin(),
        playlist.cend(),
        track
    );

    if (index == playlist.cend()) {
        return;
    }

    playlist.erase(index);
}

/**
 *
 */
void playTrack(
    const std::vector<std::string>& playlist,
    const std::string& filename
) {

    const auto index = std::find(
        playlist.cbegin(),
        playlist.cend(),
        filename
    );

    /* TODO: there are multiple reasons to exit
       the function before the end; check if using
       exceptions here is better */

    if (index == playlist.cend()) {
        return;
    }

    std::ifstream file(filename);

    if (not file.is_open()) {
        return;
    }

    std::string title;
    std::string codec;

    getline(
        file,
        title,
        '\n'
    );

    getline(
        file,
        codec,
        '\n'
    );

    /* FIXME: read duration and content */

    Track track(
        title,
        codec
    );
}

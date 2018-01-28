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
#include <thread>
#include <chrono>

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
Track loadTrack(
    const std::vector<std::string>& playlist,
    const std::string& filename
) {

    const auto index = std::find(
        playlist.cbegin(),
        playlist.cend(),
        filename
    );

    if (index == playlist.cend()) {
        throw std::invalid_argument("Track not found in playlist.");
    }

    std::ifstream file(filename);

    if (not file.is_open()) {
        throw std::invalid_argument("Cannot open the file.");
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

    return std::move(track);
}

/**
 *
 */
void playTrack(Track track) {

    for (
        auto index = 0u;
        index < 10;
        index += 1
    ) {

        std::this_thread::sleep_for(std::chrono::seconds(1));

        track.incrementPosition();
    }
}

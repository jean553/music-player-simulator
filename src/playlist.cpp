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
       then simply remove the item from the playlist
       (https://stackoverflow.com/questions/48475617/c-remove-duplicates-from-ordered-vector-of-strings) */

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
    const std::unique_ptr<Track>& track,
    std::condition_variable& cv,
    std::mutex& mutex
) {
    /* waits for the play_track command */
    std::unique_lock<std::mutex> lock(mutex);
    cv.wait(lock);

    /* this case happens when the program
       is stopped without playing any track */
    if (track == nullptr) {
        return;
    }

    while (true)
    {
        if (not track->isPlaying()) {

            /* waits for the resume command */
            cv.wait(lock);

            track->resume();

            continue;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));

        track->incrementPosition();

        if (track->getDuration() == track->getPosition()) {
            track->restart();

            if (not track->isRepeated()) {
                track->pause();
            }
        }
    }
}

/**
 *
 */
void showTrack(const std::unique_ptr<Track>& track) {

    std::cout << "Title: " << track->getTitle() << std::endl;
    std::cout << "Codec: " << track->getCodec() << std::endl;
    std::cout << "Duration: " << track->getDuration() << std::endl;
}

/**
 *
 */
void showPosition(const std::unique_ptr<Track>& track) {
    std::cout << "Current position: " << track->getPosition() << std::endl;
}

/**
 *
 */
void loadTrack(
    std::unique_ptr<Track>& track,
    std::condition_variable& cv,
    std::ifstream& file
) {

    if (track != nullptr) {
        track->pause();
    }

    std::string title;
    std::string codec;
    unsigned int duration;

    /* FIXME: #70 undefined behaviour if the file
       is not organized as expected */

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

    file >> duration;

    track.reset(
        new Track(
            title,
            codec,
            duration
        )
    );

    cv.notify_one();
} 

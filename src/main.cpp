/**
 * @file main.cpp
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "playlist.hpp"

#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <cstdlib>

/**
 * @brief displays an error message for an incorrect input
 */
void displayInputError() {
    std::cout << "Incorrect command." << std::endl;
}

/**
 *
 */
int main() {

    std::cout << "Imaginary player" << std::endl;

    srand(time(NULL));

    std::vector<std::string> playlist;
    std::string input;
    std::shared_ptr<Track> track {nullptr};
    unsigned int playedIndex {0};

    /* FIXME: wrap the thread into an unique pointer
       in order to be able to access it through
       a larger scope and also being able to know
       if it has been started or not (preventing runtime error
       when calling detach() at the end of the program);
       check if using std::task API is better */
    std::unique_ptr<std::thread> player {nullptr};

    while (true) {

        std::cout << ">>> ";

        /* use std::getline in order to
           considere multiple words */
        std::getline(
            std::cin,
            input
        );

        if (input == "exit") {
            break;
        }

        constexpr std::size_t FIRST_CHARACTER_INDEX {0};
        constexpr char SEPARATOR {' '};
        const auto separatorIndex = input.find(SEPARATOR);
        std::string command = input.substr(
            FIRST_CHARACTER_INDEX,
            separatorIndex
        );

        if (command == "list") {
            listAllTracks(playlist);
            continue;
        }

        if (command == "remove_duplicates") {
            removeDuplicates(playlist);
            continue;
        }

        if (track != nullptr) {

            if (command == "show_track") {
                showTrack(track);
                continue;
            }

            if (command == "pause") {
                track->pause();
                continue;
            }

            if (command == "resume") {
                track->resume();
                continue;
            }
        }

        if (command == "random") {

            if (track != nullptr) {
                terminateTrack(
                    track,
                    player
                );
            }

            playedIndex = rand() % playlist.size();

            loadTrack(
                track,
                player,
                playlist[playedIndex]
            );

            continue;
        }

        /* FIXME: identical code is used for both the next
           and previous commands, this code should be refactored */

        if (
            command == "next" and
            playedIndex != playlist.size() - 1
        ) {

            if (track != nullptr) {
                terminateTrack(
                    track,
                    player
                );
            }

            playedIndex += 1;

            loadTrack(
                track,
                player,
                playlist[playedIndex]
            );

            continue;
        }

        if (
            command == "previous" and
            playedIndex != 0
        ) {

            if (track != nullptr) {
                terminateTrack(
                    track,
                    player
                );
            }

            playedIndex -= 1;

            loadTrack(
                track,
                player,
                playlist[playedIndex]
            );

            continue;
        }

        if (separatorIndex == std::string::npos) {
            displayInputError();
            continue;
        }

        /* add one to do not include the prefixed space into the file name */
        std::string option = input.substr(separatorIndex + 1);

        if (option.find_first_not_of(SEPARATOR) == std::string::npos) {
            displayInputError();
            continue;
        }

        if (command == "add_track") {
            playlist.push_back(option);
        }
        else if (command == "play_track") {

            const auto index = std::find(
                playlist.cbegin(),
                playlist.cend(),
                option
            );

            if (index == playlist.cend()) {
                std::cout << "Sound not in list." << std::endl;
                continue;
            }

            if (track != nullptr) {
                terminateTrack(
                    track,
                    player
                );
            }

            playedIndex = std::distance(
                playlist.cbegin(),
                index
            );

            loadTrack(
                track,
                player,
                option
            );

            std::cout << "Playing " + track->getTitle() << std::endl;
        }
        else if (command == "remove_track") {

            removeTrack(
                playlist,
                option
            );
        } else {
            displayInputError();
        }
    }

    if (player != nullptr) {
        player->detach();
    }

    return EXIT_SUCCESS;
}

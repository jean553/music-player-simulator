/**
 * @file main.cpp
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "playlist.hpp"

#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>

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

        if (
            track != nullptr and
            command == "show_track"
        ) {
            showTrack(track);
            continue;
        }

        if (
            track != nullptr and
            command == "pause"
        ) {
            track->pause();
            continue;
        }

        if (
            track != nullptr and
            command == "resume"
        ) {
            track->resume();
            continue;
        }

        if (
            track != nullptr and
            command == "next"
        ) {
            terminateTrack(
                track,
                player
            );

            /* TODO: to define */

            continue;
        }

        if (
            track != nullptr and
            command == "previous"
        ) {
            terminateTrack(
                track,
                player
            );

            /* TODO: to define */

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

            if (track != nullptr) {
                terminateTrack(
                    track,
                    player
                );
            }

            const auto index = std::find(
                playlist.cbegin(),
                playlist.cend(),
                option
            );

            if (index == playlist.cend()) {
                std::cout << "Sound not in list." << std::endl;
                continue;
            }

            try {
                track = std::make_shared<Track>(
                    openTrack(
                        playlist,
                        option
                    )
                );
            }
            catch (std::invalid_argument& exception) {
                std::cout << exception.what() << std::endl;
                continue;
            }

            player = std::make_unique<std::thread>(
                std::thread(
                    playTrack,
                    track
                )
            );

            playedIndex = std::distance(
                playlist.cbegin(),
                index
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

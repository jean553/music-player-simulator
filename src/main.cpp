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
#include <condition_variable>
#include <fstream>

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

    srand(time(NULL));

    std::vector<std::string> playlist;
    std::string input;
    std::unique_ptr<Track> track {nullptr};
    int playedIndex {-1};
    int nextIndex {-1};

    std::condition_variable cv;
    std::mutex mutex;

    std::thread player(
        playTrack,
        std::ref(track),
        std::ref(cv),
        std::ref(mutex)
    );

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
            command == "next" or
            command == "previous" or
            command == "random"
        ) {

            if (playlist.empty()) {
                displayInputError();
                continue;
            }

            if (
                command == "next" and
                playedIndex != playlist.size() - 1
            ) {
                nextIndex += 1;
            } else if (
                command == "previous" and
                playedIndex != 0
            ) {
                nextIndex -= 1;
            } else if (command == "random") {
                nextIndex = rand() % playlist.size();
            } else {
                continue;
            }

            /* FIXME: similar code than the final
               loading track process at the end of this file */

            std::ifstream file(playlist[nextIndex]);
            if (not file.is_open()) {
                std::cout << "Cannot open file." << std::endl;
                continue;
            }

            loadTrack(
                track,
                cv,
                file
            );

            std::cout << "Playing " + playlist[nextIndex] << std::endl;

            playedIndex = nextIndex;

            continue;
        }

        std::string option;

        if (
            command == "add_track" or
            command == "play_track" or
            command == "remove_track"
        ) {

            if (separatorIndex == std::string::npos) {
                displayInputError();
                continue;
            }

            /* add one to do not include the prefixed
               space into the file name */
            option = input.substr(separatorIndex + 1);

            if (option.find_first_not_of(SEPARATOR) == std::string::npos) {
                displayInputError();
                continue;
            }

            if (command == "add_track") {
                playlist.push_back(option);
                continue;
            }

            if (command == "remove_track") {
                removeTrack(
                    playlist,
                    option
                );
                continue;
            }

            if (command == "play_track") {

                if (playlist.empty()) {
                    displayInputError();
                    continue;
                }

                const auto searchedItem = std::find(
                    playlist.cbegin(),
                    playlist.cend(),
                    option
                );

                if (searchedItem == playlist.cend()) {
                    std::cout << "Track not found." << std::endl;
                    continue;
                }

                nextIndex = std::distance(
                    playlist.cbegin(),
                    searchedItem
                );
            }

        } else {

            if (track == nullptr) {
                displayInputError();
                continue;
            }

            if (command == "show_track") {
                showTrack(track);
                continue;
            }

            if (command == "show_position") {
                showPosition(track);
                continue;
            }

            if (command == "pause") {
                track->pause();
                continue;
            }

            if (command == "resume") {
                cv.notify_one();
                continue;
            }

            if (command == "repeat") {
                track->repeat();
                continue;
            }
        }

        if (nextIndex == playedIndex) {
            continue;
        }

        std::ifstream file(playlist[nextIndex]);
        if (not file.is_open()) {
            std::cout << "Cannot open file." << std::endl;
            continue;
        }

        loadTrack(
            track,
            cv,
            file
        );

        std::cout << "Playing " + playlist[nextIndex] << std::endl;

        playedIndex = nextIndex;
    }

    cv.notify_one();
    player.detach();

    return EXIT_SUCCESS;
}

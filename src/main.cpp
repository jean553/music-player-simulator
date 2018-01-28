/**
 * @file main.cpp
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "playlist.hpp"

#include <iostream>
#include <vector>
#include <thread>

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
    std::thread player;
    std::shared_ptr<Track> track {nullptr};

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

            try {
                track = std::make_shared<Track>(
                    loadTrack(
                        playlist,
                        option
                    )
                );

                player = std::thread(
                    playTrack,
                    track
                );

                std::cout << "Playing " + track->getTitle() << std::endl;
            }
            catch (std::invalid_argument& exception) {
                std::cout << exception.what() << std::endl;
                continue;
            }
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

    /* TODO: safe solution, but it should not wait
       until the end of the thread before leaving;
       throws exception if the thread has not been started */
    player.join();

    return EXIT_SUCCESS;
}

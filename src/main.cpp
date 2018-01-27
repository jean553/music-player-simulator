/**
 * @file main.cpp
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include <iostream>
#include <vector>
#include <set>
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

            std::for_each(
                playlist.cbegin(),
                playlist.cend(),
                [](const std::string& item) {
                    std::cout << item << std::endl;
                }
            );

            continue;
        }

        if (command == "remove_duplicates") {

            /* use a temporary set to automatically remove
               all the duplicates from the playlist;
               remove every items from the playlist
               and add them back from the set */

            /* FIXME: the items should be kept ordered */

            const std::set<std::string> temporarySet(
                playlist.cbegin(),
                playlist.cend()
            );

            playlist.assign(
                temporarySet.cbegin(),
                temporarySet.cend()
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
        else if (command == "remove_track") {

            const auto index = std::find(
                playlist.cbegin(),
                playlist.cend(),
                option
            );

            if (index == playlist.cend()) {
                std::cout << "Sound not found." << std::endl;
                continue;
            }

            playlist.erase(index);

        } else {
            displayInputError();
        }
    };

    return EXIT_SUCCESS;
}

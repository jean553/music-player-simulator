/**
 * @file main.cpp
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include <iostream>
#include <vector>
#include <unordered_set>
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

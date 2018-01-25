/**
 * @file main.cpp
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include <iostream>
#include <vector>

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
        constexpr char KEYWORDS_SEPARATOR {' '};
        const auto separatorIndex = input.find(KEYWORDS_SEPARATOR);
        std::string command = input.substr(
            FIRST_CHARACTER_INDEX,
            separatorIndex
        );

        std::string option;

        try {
            option = input.substr(separatorIndex);
        }
        catch (std::out_of_range&) {
            displayInputError();
            continue;
        }

        if (command == "add_track") {

            playlist.push_back(option);
            continue;
        }

        displayInputError();
    };

    return EXIT_SUCCESS;
}

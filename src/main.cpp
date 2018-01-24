#include <iostream>

int main() {

    std::cout << "Imaginary player" << std::endl;

    std::string input;

    while (input != "exit") {

        /* use std::getline in order to
           considere multiple words */
        std::getline(
            std::cin,
            input
        );

        constexpr std::size_t FIRST_CHARACTER_INDEX {0};
        constexpr char KEYWORDS_SEPARATOR {' '};
        std::string command = input.substr(
            FIRST_CHARACTER_INDEX,
            input.find(KEYWORDS_SEPARATOR)
        );
    }

    return EXIT_SUCCESS;
}

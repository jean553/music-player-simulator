#include <iostream>
#include <vector>

/**
 * TODO: add documentation
 */
void addTrack(
    std::vector<std::string>& playlist,
    const std::string& track
) {

    /* TODO: to define */
}

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

        if (command == "add_track") {

            /* TODO: try/catch should be done before checking
               the command values, as long as we know
               that the next checked commands all require an option */
            try {
                std::string track = input.substr(separatorIndex);

                addTrack(
                    playlist,
                    track
                );
            }
            catch (std::out_of_range&) {
                std::cout << "Option required." << std::endl;
            }

            continue;
        }

        std::cout << "Unknown command." << std::endl;
    };

    return EXIT_SUCCESS;
}

#include <iostream>

int main() {

    std::cout << "Imaginary player" << std::endl;

    /* TODO: #1 comparisons of the input are made on std::string types,
       and this is clearly heavy compared to an integer comparison */

    std::string input;

    while (input != "exit") {
        std::cout << ">>> ";
        std::cin >> input;
    }

    return EXIT_SUCCESS;
}

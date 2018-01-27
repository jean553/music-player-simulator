#include "playlist.hpp"

#include <iostream>
#include <vector>
#include <algorithm>

/**
 *
 */
void listAllTracks(const std::vector<std::string>& playlist) {

    std::for_each(
        playlist.cbegin(),
        playlist.cend(),
        [](const std::string& item) {
            std::cout << item << std::endl;
        }
    );
}

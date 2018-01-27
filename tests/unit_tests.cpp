#include "playlist.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

/**
 *
 */
void testRemoveFirstTrack() {

    vector<std::string> playlist;
    playlist.push_back("z");
    playlist.push_back("y");
    playlist.push_back("x");

    removeTrack(playlist, "z");

    assert(playlist.size() == 2);
    assert(find(playlist.cbegin(), playlist.cend(), "z") == playlist.end());
    assert(find(playlist.cbegin(), playlist.cend(), "y") != playlist.end());
    assert(find(playlist.cbegin(), playlist.cend(), "x") != playlist.end());
}

/**
 *
 */
int main() {

    testRemoveFirstTrack();

    cout << "All tests passed." << endl;
    return EXIT_SUCCESS;
}

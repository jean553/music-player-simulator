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
void testRemoveMiddleTrack() {

    vector<std::string> playlist;
    playlist.push_back("z");
    playlist.push_back("y");
    playlist.push_back("x");

    removeTrack(playlist, "y");

    assert(playlist.size() == 2);
    assert(find(playlist.cbegin(), playlist.cend(), "z") != playlist.end());
    assert(find(playlist.cbegin(), playlist.cend(), "y") == playlist.end());
    assert(find(playlist.cbegin(), playlist.cend(), "x") != playlist.end());
}

/**
 *
 */
void testRemoveLastTrack() {

    vector<std::string> playlist;
    playlist.push_back("z");
    playlist.push_back("y");
    playlist.push_back("x");

    removeTrack(playlist, "x");

    assert(playlist.size() == 2);
    assert(find(playlist.cbegin(), playlist.cend(), "z") != playlist.end());
    assert(find(playlist.cbegin(), playlist.cend(), "y") != playlist.end());
    assert(find(playlist.cbegin(), playlist.cend(), "x") == playlist.end());
}

/**
 *
 */
void testRemoveAllTracks() {

    vector<std::string> playlist;
    playlist.push_back("z");
    playlist.push_back("y");
    playlist.push_back("x");

    removeTrack(playlist, "x");
    assert(playlist.size() == 2);

    removeTrack(playlist, "y");
    assert(playlist.size() == 1);

    removeTrack(playlist, "z");
    assert(playlist.size() == 0);
}

/**
 *
 */
void testRemoveTrackFromEmptyPlaylist() {

    vector<std::string> playlist;

    removeTrack(playlist, "x");

    assert(playlist.size() == 0);
}

/**
 *
 */
int main() {

    testRemoveFirstTrack();
    testRemoveMiddleTrack();
    testRemoveLastTrack();
    testRemoveAllTracks();
    testRemoveTrackFromEmptyPlaylist();

    cout << "All tests passed." << endl;
    return EXIT_SUCCESS;
}

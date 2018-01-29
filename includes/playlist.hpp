/**
 * @file playlist.hpp
 * @brief contains all the playlist operations
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef PLAYLIST_H_
#define PLAYLIST_H_

#include "track.hpp"

#include <vector>
#include <string>
#include <thread>
#include <condition_variable>

/**
 * @brief lists all the tracks
 *
 * @param playlist the playlist to list
 */
void listAllTracks(const std::vector<std::string>& playlist);

/**
 * @brief removes all the duplicates values from the playlist
 *
 * @param playlist the playlist to edit
 *
 * the passed playlist is not constant because the function
 * removes items from it if they are duplicated
 */
void removeDuplicates(std::vector<std::string>& playlist);

/**
 * @brief removes one track from the playlist
 *
 * @param playlist the playlist to edit
 * @param track the track name to remove
 *
 * the passed playlist is not constant
 * because the function might remove
 * one item from it
 */
void removeTrack(
    std::vector<std::string>& playlist,
    const std::string& track
);

/**
 * @brief simulates a track playing procedure;
 * runs a loop that increments the track position every second
 * until the position is equal to the track duration
 *
 * @param track unique pointer to the track to play
 * @param cv condition variable to start playing
 * @param mutex used with the condition variable for playing
 *
 * WARNING: the track shared pointer must not be null
 */
void playTrack(
    const std::unique_ptr<Track>& track,
    std::condition_variable& cv,
    std::mutex& mutex
);

/**
 * @brief outputs the track information
 *
 * @param track unique pointer reference to the track to analyze
 *
 * WARNING: the track unique pointer must not be null
 */
void showTrack(const std::unique_ptr<Track>& track);

/**
 * @brief loads the sound according to the file name
 *
 * @param track unique pointer reference where to load the track
 * @param filename the name of the file to load
 * @param cv condition variable to start the player thread
 * @param file the file stream to read data from
 */
void loadTrack(
    std::unique_ptr<Track>& track,
    const std::string& filename,
    std::condition_variable& cv,
    std::ifstream& file
);

#endif

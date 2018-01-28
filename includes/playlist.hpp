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
 * @brief loads the track from the given file
 *
 * @param filename the file name of the track to read (stored in the playlist)
 */
Track openTrack(const std::string& filename);

/**
 * @brief simulates a track playing procedure;
 * runs a loop that increments the track position every second
 * until the position is equal to the track duration
 *
 * @param track shared pointer to the track to play
 *
 * the shared pointer is copied as we want it to be accessible
 * from both of the playing thread and the main thread
 *
 * WARNING: the track shared pointer must not be null
 */
void playTrack(const std::shared_ptr<Track> track);

/**
 * @brief outputs the track information
 *
 * @param track shared pointer reference to the track to analyze
 *
 * WARNING: the track shared pointer must not be null
 */
void showTrack(const std::shared_ptr<Track>& track);

/**
 * @brief loads the sound according to the file name
 *
 * @param track shared pointer reference where to load the track
 * @param player unique pointer reference to the player to use
 * @param filename the name of the file to load
 */
void loadTrack(
    std::shared_ptr<Track>& track,
    std::unique_ptr<std::thread>& player,
    const std::string& filename
);

#endif

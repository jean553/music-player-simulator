/**
 * @file playlist.hpp
 * @brief contains all the playlist operations
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef PLAYLIST_H_
#define PLAYLIST_H_

#include <vector>
#include <string>

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
 * @brief loads the given file and plays sound into dedicated thread
 *
 * @param playlist the playlist to use to find tracks
 * @param filename the file name of the track to read (as stored in the playlist)
 */
void playTrack(
    const std::vector<std::string>& playlist,
    const std::string& filename
);

#endif

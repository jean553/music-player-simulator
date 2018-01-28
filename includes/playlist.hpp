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
 * @param playlist the playlist to use to find tracks
 * @param filename the file name of the track to read (stored in the playlist)
 *
 * @throws std::invalid_argument the given track
 * does not exist into the playlist or
 * the given file cannot be opened
 */
Track loadTrack(
    const std::vector<std::string>& playlist,
    const std::string& filename
);

/**
 * @brief simulate a track playing procedure
 */
void playTrack(Track track);

#endif

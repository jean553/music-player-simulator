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

#endif

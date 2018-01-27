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
 * @brief list all the tracks
 *
 * @param playlist the playlist to list
 */
void listAllTracks(const std::vector<std::string>& playlist);

#endif

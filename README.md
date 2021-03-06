[![Build Status](https://travis-ci.org/jean553/music-player-simulator.svg?branch=master)](https://travis-ci.org/jean553/music-player-simulator)

# music-player-simulator

Music playlist simulator. Provides a set of commands to manipulate basic playlist operations
(add and remove tracks, play track, play the next track, play the previous track... etc...).

**The simulated music is played into a dedicated thread**.
The playing track position is incremented by the thread: this is how is "simulated" a track execution.

The project contains:
 * the source code,
 * unit tests,
 * functional tests,
 * usage documentation (following),
 * code documentation (doxygen),
 * Travis-CI build status

The project has been successfully compiled and executed on:

 * Archlinux (01-29-2018)
   (cmake 3.10.2, g++ 7.2, doxygen 1.8.14)

```sh
sudo pacman -Ss cmake g++ doxygen
```

 * Ubuntu 17.10 (Artful)
   (cmake 3.9.1, g++ 7.2)

 * Ubuntu 14.04 (Trusty)
   (cmake 2.8.12, g++ 6)

**Note**: instead of installing manually every requirements, this is possible
to compile and run the project into a dedicated Docker container
that includes all the required tools and provides an isolated environment.
To compile and run into a container, just execute:

```sh
docker run --name music-player-simulator -t -i -v {PROJECT_PATH}:/music-player-simulator jean553/cpp-dev /bin/zsh
```

You can then follow the compilation/execution/testing steps below directly into the container shell.

## Table of contents

 - [Program](#program)
    * [Compilation](#compilation)
    * [Execution](#execution)
 - [Unit tests](#unit-tests)
    * [Compilation](#compilation)
    * [Execution](#execution)
 - [Functional tests](#functional-tests)
 - [Generate documentation](#generate-documentation)
 - [Usage](#usage)
    * [exit](#exit)
    * [add_track FILE](#add-track-FILE)
    * [remove_track FILE](#remove-track-FILE)
    * [remove_duplicates](#remove-duplicates)
    * [list](#list)
    * [next previous random](#next-previous-random)
    * [play_track_FILE](#play-track-FILE)
    * [show_track](#show-track)
    * [show_position](#show-position)
    * [pause](#pause)
    * [resume](#resume)
    * [repeat](#repeat)
 - [File format](#file-format)
 - [Improvements](#improvements)

## Program

### Compilation

```sh
mkdir build && cd build/
cmake ..
make
```

### Execution

```sh
./bin/music-player-simulator
```

## Unit tests

### Compilation

```sh
mkdir libs
g++ -c -I includes src/playlist.cpp -o libs/playlist.o
g++ -c -I includes src/track.cpp -o libs/track.o
g++ -I includes tests/unit_tests.cpp -o bin/unit_tests libs/*
```

### Execution

```sh
./bin/unit_tests
```

## Functional tests

Functional tests can be run *after the binary compilation*.

```sh
./tests/functional_tests.sh
```

## Generate documentation

```sh
doxygen
```

The documentation is generated into the `doc` folder.

## Usage

This section contains the program commands documentation.

### exit

Close the program, immediately stop the playing track.

```sh
>>> exit
```

### add_track FILE

Add the given track file at the end of the playlist.
No check is performed if the file actually exists or not
(this action is performed at the exact moment when the file is loaded for playing).

```sh
>>> add_track my_file
```

NOTE: adding a track into the playlist is not enough to play it.
Use the `play_track` command to start playing a track.

### remove_track FILE

Removes the given track file from the playlist.
If this file is playing, it won't be stopped BUT it won't be accessible once terminated either.

```sh
>>> remove_track my_file
```

### remove_duplicates

Removes all files that are stored more than once into the playlist.
Only the first file is kept.
If the playing file is removed, it won't be stopped BUT it won't be accessible once terminated either.

```sh
>>> remove_duplicates
```

### list

List all the files into the playlist (in order).

```sh
>>> list
```

### next previous random

Start playing the next track into the playlist, or the previous track,
or a randomly chosen track.

```sh
>>> next
>>> previous
>>> random
```

### play_track FILE

Plays the given track. The given file must be loaded into the playlist.

```sh
>>> play_track my_file
```

### show_track

Display information about the current playing track: title, codec and duration.

```sh
>>> show_track
```

### show_position

Display the current position of the current playing track.

```sh
>>> show_position
```

### pause

Pause the playing track. Use `resume` to unpause it.

```sh
>>> pause
```

### resume

Resume the paused playing track.

```sh
>>> resume
```

### repeat

Enable repetition for the current playing track. The track will be repeated
forever until a new track is played.

```sh
>>> repeat
```

## File format

The simulated file has the following format:

```
title
codec
duration
```

## Improvements

Here the possible improvements:
 * #71 provide a Vagrant environment to automatically install the required compilation tools with the correct version

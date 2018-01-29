[![Build Status](https://travis-ci.org/jean553/music-player-simulator.svg?branch=master)](https://travis-ci.org/jean553/music-player-simulator)

# music-player-simulator

## Compilation

```sh
mkdir build && cd build/
cmake ..
make
```

## Unit tests

### Compile object libraries

```sh
mkdir libs
g++ -c -I includes src/playlist.cpp -o libs/playlist.o
g++ -c -I includes src/track.cpp -o libs/track.o
```

### Compile and run tests

```sh
g++ -I includes tests/unit_tests.cpp -o bin/unit_tests libs/*
./bin/unit_tests
```

## Functionnal tests

Functionnal tests can be run *after the binary compilation*.

```sh
./tests/functionnal_tests.sh
```

## Generate documentation

```sh
doxygen
```

The documentation is generated into the `doc` folder.

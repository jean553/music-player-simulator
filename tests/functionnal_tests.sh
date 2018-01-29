#!/bin/sh

BINARY_PATH=./bin/music-player-simulator
INPUTS_PATH=tests/inputs
OUTPUTS_PATH=tests/outputs

OUTPUT_FILE=output
ASSERT_EQUAL_COMMAND=cmp

execute_test() {

    # execute 'echo' at the end as the output file does not have a valid EOF
    $BINARY_PATH < $INPUTS_PATH/$1 > $OUTPUT_FILE && echo "" >> output
    $ASSERT_EQUAL_COMMAND $OUTPUT_FILE $OUTPUTS_PATH/$1
}

execute_test play_track_without_track
execute_test add_tracks_and_list

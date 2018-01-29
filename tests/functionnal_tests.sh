#!/bin/sh

BINARY_PATH=./bin/music-player-simulator
INPUTS_PATH=tests/inputs
OUTPUTS_PATH=tests/outputs

OUTPUT_FILE=output
ASSERT_EQUAL_COMMAND=cmp

$BINARY_PATH < $INPUTS_PATH/play_track_without_track > $OUTPUT_FILE && echo "" >> output
$ASSERT_EQUAL_COMMAND $OUTPUT_FILE $OUTPUTS_PATH/play_track_without_track

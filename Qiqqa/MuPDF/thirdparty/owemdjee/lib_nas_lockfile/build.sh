#!/usr/bin/env bash
#
# Uses build directory ./b/
#

#cmake -Hall -Bb
cmake -Bb
cmake --build b
# ./build/standalone/test --help

#! /bin/bash
#
# Because otherwise I loose the magic incantation...
# 

mkdir build
cd build
rm *.txt
cmake -D CMAKE_FIND_DEBUG_MODE=ON -D 'CMAKE_PREFIX_PATH=../zlib;../zlib/build;../zlib/build/Debug'  ..
# cmake -D 'CMAKE_PREFIX_PATH=../zlib;../zlib/build/Debug'  ..

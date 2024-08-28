#!/bin/bash -e 

mkdir -p ./build

mkdir -p libs \
  && wget https://archives.boost.io/release/1.86.0/source/boost_1_86_0.tar.gz \
  && tar -xvf boost_1_86_0.tar.gz -C libs \
  && rm boost_1_86_0.tar.gz \
  && mv libs/boost_1_86_0 libs/boost

# Download the json lib
mkdir -p libs/nlohmann
wget -P libs/nlohmann https://github.com/nlohmann/json/releases/download/v3.11.3/json.hpp

# setup the build
cd build
cmake ..
make -j4

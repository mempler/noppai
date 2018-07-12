cmake_minimum_required(VERSION 3.10.3)

include_directories(node_modules/nan)
include_directories(lib/oppai)

add_library(noppai STATIC src/noppai.cpp lib/oppai/oppai.c src/noppai.hpp src/playmodes.hpp src/bindings.cpp src/bindings.hpp)
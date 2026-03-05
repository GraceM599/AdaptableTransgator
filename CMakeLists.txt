cmake_minimum_required(VERSION 4.0)
project(DSA_proj2)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(DSA_proj2
        src/dictionary.cpp
        src/dictionary.h
        src/HashMap.cpp
        src/HashMap.h
        src/Trie.cpp
        src/Trie.h)

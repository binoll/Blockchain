cmake_minimum_required(VERSION 3.16)
project(blockchain)

set(CMAKE_CXX_STANDARD 26)

add_executable(blockchain
        src/block/block.cpp
        src/main.cpp
)

target_include_directories(blockchain PRIVATE
        src
        libs/macos/include
)

target_link_libraries(blockchain
        ${CMAKE_SOURCE_DIR}/libs/macos/libssl.a
        ${CMAKE_SOURCE_DIR}/libs/macos/libcrypto.a
)

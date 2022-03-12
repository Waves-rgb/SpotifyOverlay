cmake_minimum_required(VERSION 3.21)
project(SpotifyOverlay)

set(CMAKE_CXX_STANDARD 20)

include_directories(dep/include)
link_directories(dep/lib)

file(GLOB_RECURSE SOURCE_FILES src/*)

link_libraries(Ws2_32.lib)
add_executable(SpotifyOverlay ${SOURCE_FILES})
cmake_minimum_required(VERSION 3.20.0)

project(game-of-life)

# The C++ Standard Version
set(CMAKE_CXX_STANDARD 14)


set(SFML_INCLUDE_DIR "/usr/local/include/SFML")
# set(SFML_LIBRARY_DIR "/usr/local/lib/")

# link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)
include_directories("${PROJECT_SOURCE_DIR}/include")

find_package (SFML 2.5 COMPONENTS system window graphics network audio)

add_executable(game-of-life
  main.cpp
  Tile.cpp
  GameBoard.cpp
)

target_link_libraries (game-of-life sfml-graphics sfml-window sfml-system)
  



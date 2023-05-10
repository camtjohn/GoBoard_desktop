cmake_minimum_required(VERSION 3.16)
project(TTT_desktop)

add_executable(game)
target_include_directories(game PRIVATE "$PROJECT_SOURCE_DIR}")
add_subdirectory(main)

install(TARGETS game)

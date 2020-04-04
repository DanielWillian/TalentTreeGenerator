cmake_minimum_required(VERSION 3.10)

project(TalentTree VERSION 0.1)

set(WARNING_FLAGS_MSVC /W4)
set(WARNING_FLAGS_NON_MSVC -Wall)

add_subdirectory(${PROJECT_SOURCE_DIR}/Source)


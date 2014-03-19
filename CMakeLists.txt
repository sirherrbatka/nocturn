project(nocturn)
set(CMAKE_AUTOMOC ON)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)

cmake_minimum_required(VERSION  2.8.11)

ADD_DEFINITIONS(
    -std=c++11 # Or -std=c++0x
    # Other flags
)

option(BUILD_UNITTESTS "Enable Unittests with Google C++ Unittest ang GMock frameworks" OFF)

add_subdirectory(app/)

if (BUILD_UNITTESTS)
add_subdirectory(tests/)
endif()

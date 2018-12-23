cmake_minimum_required(VERSION 3.13)

# Project name
project(CactuJam)
set(EXECUTABLE_NAME CactuJam)

# Directories
set(DIR_SOURCE source)
set(DIR_BIN bin)

# C++17
set(CMAKE_CXX_STANDARD 17)

# EXE
file(GLOB ALL_SOURCE_FILES
        "${DIR_SOURCE}/*"
        "${DIR_SOURCE}/utilities/*"
        "${DIR_SOURCE}/utilities/graphics/*"
        "${DIR_SOURCE}/stages/*"
        "${DIR_SOURCE}/maps/*"
        "${DIR_SOURCE}/maps/tiles/*"
        "${DIR_SOURCE}/characters/*"
    )

add_executable(${EXECUTABLE_NAME} ${ALL_SOURCE_FILES})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR}/${DIR_BIN})
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake-modules" ${CMAKE_MODULE_PATH})
include(${CMAKE_CURRENT_LIST_DIR}/cmake-modules/Config.cmake)

# LUA
find_package(Lua51 REQUIRED)
include_directories(${LUA_ROOT})
target_link_libraries(${EXECUTABLE_NAME} ${LUA_LIBRARIES})

# Sol2 Library
include_directories(${SOL2_ROOT})

# SFML
include_directories("${CMAKE_CURRENT_LIST_DIR}/${SFML_ROOT}/include")
find_package(SFML COMPONENTS system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

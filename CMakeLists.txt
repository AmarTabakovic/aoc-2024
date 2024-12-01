cmake_minimum_required(VERSION 3.16)

project(aoc-2024 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

include_directories(${CMAKE_SOURCE_DIR}/src)

file(GLOB DAY_DIRECTORIES "${SRC_DIR}/day-*")

foreach(DAY_DIR ${DAY_DIRECTORIES})
    if (IS_DIRECTORY ${DAY_DIR})
      get_filename_component(APP_NAME ${DAY_DIR} NAME)
      add_subdirectory(${DAY_DIR} ${CMAKE_BINARY_DIR}/${APP_NAME})
    endif()
endforeach()

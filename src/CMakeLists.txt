#
# Copyright (C) 2018-2020 QuasarApp.
# Distributed under the lgplv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

cmake_minimum_required(VERSION 3.10)
set(CURRENT_PROJECT ${PROJECT_NAME})

add_subdirectory(mini-gmp)

include(mini-gmp/CMake/ProjectOut.cmake)
include(mini-gmp/CMake/Version.cmake)


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DPATRONUM_LIBRARY)

find_package(Qt5 COMPONENTS Core Test REQUIRED)

file(GLOB SOURCE_CPP
    "Qt-AES/qaesencryption.cpp"
    "Qt-RSA/*.cpp"
    "*.cpp"
)

add_library(${CURRENT_PROJECT} SHARED ${SOURCE_CPP})
target_link_libraries(${CURRENT_PROJECT} PUBLIC Qt5::Core QtBigint)
target_include_directories(${CURRENT_PROJECT} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Qt-AES")
target_include_directories(${CURRENT_PROJECT} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Qt-RSA")

file(GLOB SOURCE_CPP_AES
    "Qt-AES/main.cpp"
    "Qt-AES/unit_test/*.cpp"

)

add_executable("${CURRENT_PROJECT}AES_TEST" ${SOURCE_CPP_AES})
target_link_libraries("${CURRENT_PROJECT}AES_TEST" PUBLIC Qt5::Core Qt5::Test ${CURRENT_PROJECT} QtBigint)
target_include_directories("${CURRENT_PROJECT}AES_TEST" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Qt-AES/unit_test")

include(mini-gmp/CMake/QuasarAppCITargets.cmake)
initTests()
addTests("AES_TEST" "${CURRENT_PROJECT}AES_TEST")

setVersion(1 3 0)

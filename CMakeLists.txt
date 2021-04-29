#
# Copyright (C) 2018-2021 QuasarApp.
# Distributed under the lgplv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

cmake_minimum_required(VERSION 3.10)
project(Qt-Secret LANGUAGES CXX)
if(TARGET ${PROJECT_NAME})
  message("The ${PROJECT_NAME} arledy included in main Project")
  return()
endif()

include(src/mini-gmp/CMake/QuasarApp.cmake)
include(src/mini-gmp/CMake/Version.cmake)

if (NOT DEFINED QTSECRET_TESTS)
    set(QTSECRET_TESTS ON)

    if (DEFINED TARGET_PLATFORM_TOOLCHAIN)
        if (${TARGET_PLATFORM_TOOLCHAIN} STREQUAL "wasm32")
            set(QTSECRET_TESTS OFF)
        endif()
    endif()

    if (ANDROID)
        set(QTSECRET_TESTS OFF)
    endif()
endif()

if (NOT DEFINED QTSECRET_GUI)
    set(QTSECRET_GUI ON)

    if (DEFINED TARGET_PLATFORM_TOOLCHAIN)
        if (${TARGET_PLATFORM_TOOLCHAIN} STREQUAL "wasm32")
            set(QTSECRET_GUI OFF)
        endif()
    endif()

    if (ANDROID)
        set(QTSECRET_GUI OFF)
    endif()
endif()

# Add sub directories
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

# Add sub directories
add_subdirectory(src/mini-gmp)
add_subdirectory(src)
if (QTSECRET_TESTS)
    add_subdirectory(tests)
endif()

IF(QTSECRET_GUI)
    message("The GUI Example is enabled")
    add_subdirectory(Qt-Secret-GUI)
else()
    message("The GUI Example is disabled")
endif()

initAll()

addDoc("Qt-Secret" ${CMAKE_CURRENT_SOURCE_DIR}/doxygen.conf)


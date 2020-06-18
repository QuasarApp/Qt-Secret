#
# Copyright (C) 2018-2020 QuasarApp.
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

include(src/mini-gmp/CMake/ccache.cmake)
# Add sub directories
add_subdirectory(src)
add_subdirectory(tests)

IF(NOT DEFINED WITHOUT_GUI)
    message("The GUI Example is enabled")
    add_subdirectory(Qt-Secret-GUI)
else()
    message("The GUI Example is disabled")
endif()

include(src/mini-gmp/CMake/QuasarAppCITargets.cmake)
initAll()

addDoc("Qt-Secret" ${CMAKE_CURRENT_SOURCE_DIR}/doxygen.conf)


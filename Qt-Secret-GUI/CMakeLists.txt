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

include(Patronum/QuasarAppLib/CMake/ccache.cmake)
# Add sub directories
add_subdirectory(Patronum)
add_subdirectory(Tests)

include(Patronum/QuasarAppLib/CMake/QuasarAppCITargets.cmake)
initAll()

addDoc("Patronum" ${CMAKE_CURRENT_SOURCE_DIR}/doxygen.conf)


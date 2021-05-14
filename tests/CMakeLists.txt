#
# Copyright (C) 2018-2021 QuasarApp.
# Distributed under the lgplv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

cmake_minimum_required(VERSION 3.10)

set(CURRENT_PROJECT ${PROJECT_NAME}Test)


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Test REQUIRED)

# RSA TESTS
file(GLOB SOURCE_CPP
    "*.cpp"
)

add_executable("${CURRENT_PROJECT}_RSA" ${SOURCE_CPP})
target_link_libraries("${CURRENT_PROJECT}_RSA" PRIVATE Qt-Secret)
target_include_directories("${CURRENT_PROJECT}_RSA" PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# AES TESTS
file(GLOB SOURCE_CPP_AES
    "../src/Qt-AES/main.cpp"
    "../src/Qt-AES/unit_test/*.cpp"
    "../src/Qt-AES/res.qrc"

)

add_executable("${CURRENT_PROJECT}_AES" ${SOURCE_CPP_AES})
target_link_libraries("${CURRENT_PROJECT}_AES" PUBLIC Qt${QT_VERSION_MAJOR}::Test Qt-Secret)
target_include_directories("${CURRENT_PROJECT}_AES" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../src/Qt-AES/unit_test")


addTests("Qt-SecretRSA" "${CURRENT_PROJECT}_RSA")
addTests("Qt-SecretAES" "${CURRENT_PROJECT}_AES")

cmake_minimum_required(VERSION 3.16.2)

project(utaglib LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_PREFIX_PATH=/usr/local/Cellar/qt/5.15.1/)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(TARGET utaglib)
set(SOURCES mainwindow.cpp sorting.cpp slots.cpp)

add_library(${TARGET} ${SOURCES})

target_include_directories(${TARGET} PUBLIC ${Qt5Widgets_INCLUDE_DIRS})
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../taglib
                        ${CMAKE_CURRENT_SOURCE_DIR}/../../taglib/toolkit
                        ${CMAKE_CURRENT_SOURCE_DIR}/../../taglib/asf
                        ${CMAKE_CURRENT_SOURCE_DIR}/../../taglib/mpeg
                        ${CMAKE_CURRENT_SOURCE_DIR}/../../taglib/ogg
                        ${CMAKE_CURRENT_SOURCE_DIR}/../../taglib/ogg/flac
                        ${CMAKE_CURRENT_SOURCE_DIR}/../../taglib/flac
                        ${CMAKE_CURRENT_SOURCE_DIR}/../../taglib/mpc
                        ${CMAKE_CURRENT_SOURCE_DIR}/../../taglib/mp4
                        ${CMAKE_CURRENT_SOURCE_DIR}/../../taglib/ogg/vorbis
                        ${CMAKE_CURRENT_SOURCE_DIR}/../../taglib/ogg/speex
                        ${CMAKE_CURRENT_SOURCE_DIR}/../../taglib/ogg/opus
                        ${CMAKE_CURRENT_SOURCE_DIR}/../../taglib/mpeg/id3v2
                        ${CMAKE_CURRENT_SOURCE_DIR}/../../taglib/mpeg/id3v2/frames
                        ${CMAKE_CURRENT_SOURCE_DIR}/../../taglib/mpeg/id3v1
                        ${CMAKE_CURRENT_SOURCE_DIR}/../../taglib/ape
                        ${CMAKE_CURRENT_SOURCE_DIR}/../../taglib/wavpack
                        ${CMAKE_CURRENT_SOURCE_DIR}/../../taglib/trueaudio
                        ${CMAKE_CURRENT_SOURCE_DIR}/../../taglib/riff
                        ${CMAKE_CURRENT_SOURCE_DIR}/../../taglib/riff/aiff
                        ${CMAKE_CURRENT_SOURCE_DIR}/../../taglib/riff/wav
                        ${CMAKE_CURRENT_SOURCE_DIR}/../../taglib/mod
                        ${CMAKE_CURRENT_SOURCE_DIR}/../../taglib/s3m
                        ${CMAKE_CURRENT_SOURCE_DIR}/../../taglib/it
                        ${CMAKE_CURRENT_SOURCE_DIR}/../../taglib/xm)

target_link_libraries(${TARGET} PRIVATE Qt5::Widgets)
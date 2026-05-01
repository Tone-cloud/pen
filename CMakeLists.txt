cmake_minimum_required(VERSION 3.16)
project(clock_plugin LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Qml Quick)

add_library(clock_plugin SHARED
    src/clock_controller.cpp
    src/clock_qml_plugin.cpp
)

target_include_directories(clock_plugin PRIVATE src)

target_link_libraries(clock_plugin
    PRIVATE
        Qt5::Core
        Qt5::Qml
        Qt5::Quick
)

set_target_properties(clock_plugin PROPERTIES
    OUTPUT_NAME "clock_plugin"
)

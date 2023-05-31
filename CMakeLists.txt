cmake_minimum_required(VERSION 3.5)

project(LifeApp VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/forms)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

add_subdirectory(lib/LifeLib)
add_subdirectory(src)

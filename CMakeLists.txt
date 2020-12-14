project(cw2)
cmake_minimum_required(VERSION 3.15)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "D:/Qt_source/qt/5.14.2/mingw73_64")

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5MultimediaWidgets REQUIRED)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


add_executable(app
        the_button.cpp
        the_player.cpp
        tomeo.cpp
        )

target_link_libraries(app Qt5::Core)
target_link_libraries(app Qt5::Gui)
target_link_libraries(app Qt5::Widgets)
target_link_libraries(app Qt5::Multimedia)
target_link_libraries(app Qt5::MultimediaWidgets)

project(cw2)
cmake_minimum_required(VERSION 3.15)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "D:/Qt/Qt5.14.2/5.14.2/mingw73_64")

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5MultimediaWidgets REQUIRED)



add_executable(app
        fullscreen_button.h
        nextvideo_button.h
        player_layout.h
        playpause.h
        skip_buttons.h
        the_button.h
        the_player.h
        video_slider.h
        video_widget.h
        videolength_label.h
        videosearch.h
        volume.h

        the_button.cpp
        the_player.cpp
        tomeo.cpp
        player_layout.cpp
        playpause.cpp
        video_slider.cpp
        video_widget.cpp
        videolength_label.cpp
        videosearch.cpp
        volume.cpp
        )

target_link_libraries(app Qt5::Core)
target_link_libraries(app Qt5::Gui)
target_link_libraries(app Qt5::Widgets)
target_link_libraries(app Qt5::Multimedia)
target_link_libraries(app Qt5::MultimediaWidgets)

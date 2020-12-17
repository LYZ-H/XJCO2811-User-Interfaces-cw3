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
        full_screen.h
        length_label.h
        next_video.h
        skip_buttons.h
        the_button.h
        the_layout.h
        the_pause.h
        the_player.h
        tomeo.h
        video_search.h
        video_slider.h
        video_volume.h
        video_widget.h

        length_label.cpp
        the_button.cpp
        the_layout.cpp
        the_pause.cpp
        the_player.cpp
        tomeo.cpp
        video_search.cpp
        video_slider.cpp
        video_volume.cpp
        video_widget.cpp
        )

target_link_libraries(app Qt5::Core)
target_link_libraries(app Qt5::Gui)
target_link_libraries(app Qt5::Widgets)
target_link_libraries(app Qt5::Multimedia)
target_link_libraries(app Qt5::MultimediaWidgets)

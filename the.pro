QT += core gui widgets multimedia multimediawidgets

CONFIG += c++11


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        length_label.cpp \
        the_button.cpp \
        the_layout.cpp \
        the_pause.cpp \
        the_player.cpp \
        tomeo.cpp \
        video_search.cpp \
        video_slider.cpp \
        video_volume.cpp \
        video_widget.cpp

HEADERS += \
    full_screen.h \
    length_label.h \
    next_video.h \
    the_button.h \
    the_layout.h \
    the_pause.h \
    the_player.h \
    video_search.h \
    video_slider.h \
    video_volume.h \
    video_widget.h \
    skip_buttons.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



#include <QScrollArea>
#include <QScrollBar>
#include <iostream>
#include <QVideoWidget>
#include <QSlider>
#include <QComboBox>
#include <QStyle>

#include "the_layout.h"
#include "the_button.h"
#include "video_volume.h"
#include "skip_buttons.h"
#include "the_pause.h"
#include "length_label.h"
#include "full_screen.h"
#include "video_search.h"
#include "next_video.h"

using namespace std;

void ResponsiveLayout::setGeometry(const QRect &r) {

    QLayout::setGeometry(r);

    //iterates through all of our added widgets
    for (int i = 0; i < list_.size(); i++) {

        QLayoutItem *o = list_.at(i);

        //then specific geometries will be set for each one, depending on the widget
        try {
            QFrame *frame = dynamic_cast<QFrame *>(o->widget());
            QScrollArea *qw = dynamic_cast<QScrollArea *>(o->widget());
            QVideoWidget *videoWidget = dynamic_cast<QVideoWidget *>(o->widget());
            QSlider *videoSlider = dynamic_cast<QSlider *>(o->widget());
            VolumeSlider *volumeSlider = dynamic_cast<VolumeSlider *>(o->widget());
            FullScreenButton *fullScreen = dynamic_cast<FullScreenButton *>(o->widget());

            if (r.width() > r.height()){
                landscapeMode(frame, qw, videoWidget, videoSlider, volumeSlider,
                              fullScreen, r);

            } else { //portrait mode
                portraitMode(frame, qw, videoWidget, videoSlider, volumeSlider,
                             fullScreen, r);
            }
        }
        catch (bad_cast) {
            // bad_case: cast failed on reference...
            cout << "warning, unknown widget class in layout" << endl;
        }
    }
}

void ResponsiveLayout::landscapeMode(QFrame *frame, QScrollArea *qw, QVideoWidget *videoWidget,
                                     QSlider *videoSlider, VolumeSlider *volumeSlider,
                                     FullScreenButton *fullScreen, const QRect &r) {
    if (qw) {
        qw->setGeometry(r.width() - 250, r.y(), 250, r.height());
    } else if (videoWidget && !videoWidget->isFullScreen()) {
        videoWidget->setGeometry(0 + r.x(), 0, r.width() - 250, r.height() - 95);
    } else if (videoWidget && videoWidget->isFullScreen()) {
        videoWidget->showFullScreen();
    } else if (volumeSlider) {
        volumeSlider->setGeometry(r.x() + 255, r.height() - 46, 0.8 * r.width() - 475, 30);
    } else if (videoSlider) {
        videoSlider->setGeometry(r.x() + 15, r.height() - 88, r.width() - 410, 30);
    } else if (fullScreen) {
        fullScreen->setGeometry(r.x() + 0.8 * r.width() - 205,
                                r.height() - 50.5, 0.2 * r.width() - 60, 40);
    } else if (frame->whatsThis() == "duration_label") {
        frame->setGeometry(r.x() + r.width() - 315, r.height() - 88, 60, 30);
    } else if (frame->whatsThis() == "length_label") {
        frame->setGeometry(r.x() + r.width() - 375, r.height() - 88, 60, 30);
    } else if (frame->whatsThis() == "buttons") {
        frame->setGeometry(r.x(), r.height() - 60, 265, 60);
    }
}

void ResponsiveLayout::portraitMode(QFrame *frame, QScrollArea *qw, QVideoWidget *videoWidget,
                                     QSlider *videoSlider, VolumeSlider *volumeSlider,
                                     FullScreenButton *fullScreen, const QRect &r) {
    if(qw) {
        qw->setGeometry(0 + r.x(), r.height() - 220 + r.y(), r.width(), 220);
    } else if (videoWidget && !videoWidget->isFullScreen()) {
           videoWidget->setGeometry(0 + r.x(), 0, r.width(), 0.625 * r.height() - 35);
    } else if (videoWidget && videoWidget->isFullScreen()) {
           videoWidget->showFullScreen();
    } else if (volumeSlider) {
        volumeSlider->setGeometry(270 + r.x(), 0.625 * r.height() + 25, r.width() - 425, 30);
    } else if (videoSlider) {
        videoSlider->setGeometry(r.x() + 15, 0.625 * r.height() - 25, r.width() - 150, 30);
    } else if (fullScreen) {
        fullScreen->setGeometry(r.width() - 130, 0.625 * r.height() + 19, 120, 40);
    } else if (frame->whatsThis() == "length_label") {
        frame->setGeometry(r.width() - 120, 0.625 * r.height() - 25, 60, 30);
    } else if (frame->whatsThis() == "duration_label") {
        frame->setGeometry(r.width() - 60, 0.625 * r.height() - 25, 60, 30);
    } else if (frame->whatsThis() == "buttons") {
        frame->setGeometry(5 + r.x(), 0.625 * r.height() + 10, 265, 60);
    }
}

// following methods provide a trivial list-based implementation of the QLayout class
int ResponsiveLayout::count() const {
    return list_.size();
}

QLayoutItem *ResponsiveLayout::itemAt(int idx) const {
    return list_.value(idx);
}

QLayoutItem *ResponsiveLayout::takeAt(int idx) {
    return idx >= 0 && idx < list_.size() ? list_.takeAt(idx) : 0;
}

void ResponsiveLayout::addItem(QLayoutItem *item) {
    list_.append(item);
}

QSize ResponsiveLayout::sizeHint() const {
    return minimumSize();
}

QSize ResponsiveLayout::minimumSize() const {
    return QSize(300,300);
}

// the all area of the outside of scroll parts
void ResponsiveLayout::setScrollArea(QScrollArea *scrollArea) {
    this -> scrollAreaPart = scrollArea;
}

ResponsiveLayout::~ResponsiveLayout() {
    QLayoutItem *item;
    while ((item = takeAt(0))) {
        delete item;
    }
}

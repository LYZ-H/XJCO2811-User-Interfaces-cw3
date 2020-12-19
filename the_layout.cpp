
#include <QScrollArea>
#include <QScrollBar>
#include <iostream>
#include <QVideoWidget>
#include <QSlider>
#include <QComboBox>
#include <QStyle>

#include "the_layout.h"
#include "the_button.h"
#include "the_pause.h"
#include "length_label.h"
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

            if (r.width() > r.height()){
                landscapeMode(frame, qw, videoWidget, videoSlider, r);

            } else { //portrait mode
                portraitMode(frame, qw, videoWidget, videoSlider, r);
            }
        }
        catch (bad_cast) {
            // bad_case: cast failed on reference...
            cout << "warning, unknown widget class in layout" << endl;
        }
    }
}

void ResponsiveLayout::landscapeMode(QFrame *frame, QScrollArea *qw, QVideoWidget *videoWidget,
                                     QSlider *videoSlider, const QRect &r) {
    if (qw) {
        qw->setGeometry(r.width() - 250 + r.x(), r.y(), 250, r.height());
    } else if (videoWidget) {
        videoWidget->setGeometry(0 + r.x(), 0 + r.y(), r.width() - 250, r.height() - 105);
    } else if (videoSlider) {
        videoSlider->setGeometry(r.x() + 10, r.height() - 94 + r.y(), r.width() - 385, 30);
    } else if (frame->whatsThis() == "duration_label") {
        frame->setGeometry(r.x() + r.width() - 305 + r.y(), r.height() - 94, 60, 30);
    } else if (frame->whatsThis() == "length_label") {
        frame->setGeometry(r.x() + r.width() - 365, r.height() - 94 + r.y(), 60, 30);
    } else if (frame->whatsThis() == "buttons") {
        frame->setGeometry(0.5 * (r.width()-250) - 131 + r.x(), r.height() - 66 + r.y(), 265, 60);
    }
}

void ResponsiveLayout::portraitMode(QFrame *frame, QScrollArea *qw, QVideoWidget *videoWidget,
                                    QSlider *videoSlider, const QRect &r) {
    if(qw) {
        qw->setGeometry(0 + r.x(), 0.6 * r.height() + 48 + r.y(),
                        r.width(), 0.4 * r.height() - 48);
    } else if (videoWidget) {
        videoWidget->setGeometry(0 + r.x(), 0, r.width(), 0.6 * r.height() - 10);
    } else if (videoSlider) {
        videoSlider->setGeometry(r.x() + 54, 0.6 * r.height() + 5, r.width() - 180, 30);
    } else if (frame->whatsThis() == "length_label") {
        frame->setGeometry(r.width() - 115, 0.6 * r.height() + 5, 60, 30);
    } else if (frame->whatsThis() == "duration_label") {
        frame->setGeometry(r.width() - 57, 0.6 * r.height() + 5, 60, 30);
    } else if (frame->whatsThis() == "buttons") {
        frame->setGeometry(r.x() - 4, 0.6 * r.height() - 10, 60, 60);
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

ResponsiveLayout::~ResponsiveLayout() {
    QLayoutItem *item;
    while ((item = takeAt(0))) {
        delete item;
    }
}

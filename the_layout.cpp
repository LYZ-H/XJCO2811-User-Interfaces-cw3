
#include <QScrollArea>
#include <QScrollBar>
#include <iostream>
#include <QVideoWidget>
#include <QSlider>
#include <QComboBox>
#include <QStyle>

#include "the_layout.h"
#include "the_button.h"

using namespace std;

void ResponsiveLayout::setGeometry(const QRect &r) {

    QLayout::setGeometry(r);

    //iterates through all of our added widgets
    for (int i = 0; i < list_.size(); i++) {

        QLayoutItem *o = list_.at(i);

        //then specific geometries will be set for each one, depending on the widget
        try {
            QScrollArea *qw = dynamic_cast<QScrollArea *>(o->widget());
            QVideoWidget *videoWidget = dynamic_cast<QVideoWidget *>(o->widget());

            if (r.width() > r.height()){
                if (qw) {
                    qw->setGeometry(r.width() - 249, r.y(), 250, r.height());
                } else if (videoWidget) {
                    videoWidget->setGeometry(0 + r.x(), 0, r.width() - 250, r.height());
                }

            } else { //portrait mode
                if(qw) {
                    qw->setGeometry(0 + r.x(), 0.7 * r.height() - 34 + r.y(),
                     r.width(), 0.3 * r.height() + 36);
                } else if (videoWidget) {
                       videoWidget->setGeometry(0 + r.x(), 0, r.width(), 0.7 * r.height() - 35);
                }
            }
        }
        catch (bad_cast) {
            // bad_case: cast failed on reference...
            cout << "warning, unknown widget class in layout" << endl;
        }
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

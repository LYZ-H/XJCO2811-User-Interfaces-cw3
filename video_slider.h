#ifndef VIDEO_SLIDER_H
#define VIDEO_SLIDER_H


#include <QPushButton>
#include <QStyle>
#include <QWidget>
#include <QSlider>
#include <QApplication>
#include <QMouseEvent>
#include "the_player.h"

class VideoSlider : public QSlider {
Q_OBJECT
public:
    explicit VideoSlider(QWidget *parent) : QSlider(Qt::Horizontal, parent) {
        setTracking(true);
        setRange(0, 0); //range is initially set to 0
        setStyleSheet("QSlider {\
                          margin: 10 -4 -4 -4;\
                          padding-bottom: 10px;\
                      }\
                      QSlider::add-page {\
                          background-color: rgb(205,205,205);\
                          height:5px;\
                          border-radius: 2px;\
                      }\
                      QSlider::sub-page {\
                          background-color:rgb(0,163,217);\
                          height:5px;\
                          border-radius: 2px;\
                      }\
                      QSlider::groove {\
                          background:transparent;\
                          height:6px;\
                      }\
                      QSlider::handle {\
                          height: 13px;\
                          width: 13px;\
                          margin: -4 0 -4 0;\
                          border-radius: 7px;\
                          background: white;\
                          border: 1px solid black;\
                      }");
    }

protected:
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            double pos_val = minimum() + ((maximum() - minimum()) * event->x()) / width();
            setValue(pos_val);
            sliderMoved(pos_val);
            event->accept();
        }
        QSlider::mousePressEvent(event);
    }

    void mouseReleaseEvent(QMouseEvent *event) override {
        mouseRelease();
        event->accept();
        QSlider::mouseReleaseEvent(event);
    }

private:
signals:

    void mouseRelease();

private slots:

    void SetValue(qint64 volume);

    //this slot is used to set slider range to the correct duration
    void SetRange(qint64 volume);
};

#endif // VIDEO_SLIDER_H

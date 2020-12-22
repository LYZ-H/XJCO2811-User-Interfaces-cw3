#ifndef VIDEO_VOLUME_H
#define VIDEO_VOLUME_H


#include <QPushButton>
#include <QStyle>
#include <QWidget>
#include <QSlider>
#include <QStyleFactory>
#include <QMouseEvent>
#include <QApplication>
#include <QtDebug>

class VolumeButton : public QPushButton {
Q_OBJECT

public:
    explicit VolumeButton(QWidget *parent) : QPushButton(parent) {
        setIconSize(QSize(40, 40));
        setFixedSize(40, 40);
        setFlat(true);
        setIconSize(QSize(20, 20));
        setStyleSheet("QPushButton:hover{border-radius:20;background-color:rgba(0,0,0,25); }"
                      "QPushButton:pressed{border-radius:20;background-color:rgba(0,0,0,75); }");
        //qstyle used to set button icon
        connect(this, SIGNAL(released()), this, SLOT(clicked()));
    }

    //boolean for muted or not
    void setMute(bool flipMute);

private slots:

    void clicked();

    //icon changes depending on muted or not
    void changeIcon(int volVal);

signals:

    void mute(bool muted);

    //allows button to affect the slider
    void moveSlider(int volume);

private:
    //video starts muted
    bool muteValue = true;
};


class VolumeSlider : public QSlider {
Q_OBJECT
public:
    explicit VolumeSlider(QWidget *parent) : QSlider(Qt::Horizontal, parent) {
        setTracking(true);
        setRange(0, 6400);
        setValue(1600);
        setSingleStep(1);
        setStyleSheet("QSlider {\
                          margin: 10 10 -4 -4;\
                          padding-bottom: 10px;\
                      }\
                      QSlider::add-page {\
                          background-color: rgb(205,205,205);\
                          height:5px;\
                          border-radius: 2px;\
                      }\
                      QSlider::sub-page {\
                          background-color:rgb(2, 10, 82);\
                          height:5px;\
                          border-radius: 2px;\
                      }\
                      QSlider::groove {\
                          background:transparent;\
                          height:6px;\
                      }\
                      QSlider::handle {\
                          height: 8px;\
                          width: 8px;\
                          margin: 0 0 0 0;\
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


private slots:

    void moveSlider(qint64 volume);
};

#endif // VIDEO_VOLUME_H

#ifndef VIDEO_VOLUME_H
#define VIDEO_VOLUME_H


#include <QPushButton>
#include <QStyle>
#include <QWidget>
#include <QSlider>
#include <QStyleFactory>

class VolumeButton : public QPushButton {
    Q_OBJECT

public:
     VolumeButton(QWidget *parent) : QPushButton(parent) {
         setIconSize(QSize(40,40));
         setFixedSize(40,40);
         setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
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
    VolumeSlider(QWidget *parent) : QSlider(Qt::Horizontal, parent) {
        setStyle(QStyleFactory::create("Fusion"));
        setTracking(true);
        setRange(0,100);
   }

private slots:
    void moveSlider(int volume);
};

#endif // VIDEO_VOLUME_H

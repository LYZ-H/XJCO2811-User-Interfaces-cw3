#ifndef THE_PAUSE_H
#define THE_PAUSE_H


#include <QPushButton>
#include <QStyle>
#include <QWidget>
#include <QMediaPlayer>


class PlayButton : public QPushButton {
    Q_OBJECT
public:
    PlayButton(QWidget *parent) : QPushButton(parent) {
        setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        setFixedSize(40,40);
        //we use the QStyle in built icons for our play button
   }
private slots:
    //void clicked();
    void setState(QMediaPlayer::State state);
};


#endif // THE_PAUSE_H

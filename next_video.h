#ifndef NEXT_VIDEO_H
#define NEXT_VIDEO_H


#include <QPushButton>
#include <QStyle>
#include <QWidget>

class NextButton : public QPushButton {
    Q_OBJECT
public:
    NextButton(QWidget *parent) : QPushButton(parent) {
        setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
        setFixedSize(40,40);
   }

};
// as with the play button, QStyle is used for the button icon
class PrevButton : public QPushButton {
    Q_OBJECT
public:
    PrevButton(QWidget *parent) : QPushButton(parent) {
        setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
        setFixedSize(40,40);
   }

};

#endif // NEXT_VIDEO_H

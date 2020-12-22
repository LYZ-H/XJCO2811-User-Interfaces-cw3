#ifndef NEXT_VIDEO_H
#define NEXT_VIDEO_H


#include <QPushButton>
#include <QStyle>
#include <QWidget>

class NextButton : public QPushButton {
    Q_OBJECT
public:
    NextButton(QWidget *parent) : QPushButton(parent) {
        setIcon(QIcon(":/next.svg"));
        setFixedSize(40,40);
        setFlat(true);
        setStyleSheet("QPushButton:hover{border-radius:20;background-color:rgba(0,0,0,25); }"
                    "QPushButton:pressed{border-radius:20;background-color:rgba(0,0,0,75); }");
   }

};
// as with the play button, QStyle is used for the button icon
class PrevButton : public QPushButton {
    Q_OBJECT
public:
    PrevButton(QWidget *parent) : QPushButton(parent) {
        setIcon(QIcon(":/back.svg"));
        setFixedSize(40,40);
        setFlat(true);
        setStyleSheet("QPushButton:hover{border-radius:20;background-color:rgba(0,0,0,25); }"
                    "QPushButton:pressed{border-radius:20;background-color:rgba(0,0,0,75); }");
   }

};

#endif // NEXT_VIDEO_H

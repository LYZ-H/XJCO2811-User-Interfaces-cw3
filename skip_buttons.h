#ifndef SKIP_BUTTONS_H
#define SKIP_BUTTONS_H


#include <QPushButton>
#include <QStyle>
#include <QWidget>

class ForwardButton : public QPushButton {
    Q_OBJECT
public:
    ForwardButton(QWidget *parent) : QPushButton(parent) {
        setIcon(QIcon(":/forwardSkipBtn.svg"));
        setFixedSize(40,40);
        setFlat(true);
        setStyleSheet("QPushButton:hover{border-radius:20;background-color:rgba(0,0,0,25); }"
                    "QPushButton:pressed{border-radius:20;background-color:rgba(0,0,0,75); }");
   }

};
// as with the play button, QStyle is used for the button icon
class BackwardButton : public QPushButton {
    Q_OBJECT
public:
    BackwardButton(QWidget *parent) : QPushButton(parent) {
        setIcon(QIcon(":/backwardSkipBtn.svg"));
        setFixedSize(40,40);
        setFlat(true);
        setStyleSheet("QPushButton:hover{border-radius:20;background-color:rgba(0,0,0,25); }"
                    "QPushButton:pressed{border-radius:20;background-color:rgba(0,0,0,75); }");
   }

};

#endif // SKIP_BUTTONS_H

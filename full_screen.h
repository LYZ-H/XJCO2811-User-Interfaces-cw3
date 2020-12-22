#ifndef FULL_SCREEN_H
#define FULL_SCREEN_H


#include <QPushButton>
#include <QWidget>

class FullScreenButton : public QPushButton {
Q_OBJECT
public:
    explicit FullScreenButton(QWidget *parent) : QPushButton(parent) {
        //constructor sets the geometry of the full screen button
        setIcon(QIcon(":/fill.svg"));
        setFixedSize(40, 40);
        setFlat(true);
        setStyleSheet("QPushButton:hover{border-radius:20;background-color:rgba(0,0,0,25); }"
                      "QPushButton:pressed{border-radius:20;background-color:rgba(0,0,0,75); }"
                      );
    }

};

#endif // FULL_SCREEN_H

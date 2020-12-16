#ifndef FULL_SCREEN_H
#define FULL_SCREEN_H


#include <QPushButton>
#include <QWidget>

class FullScreenButton : public QPushButton {
    Q_OBJECT
public:
    FullScreenButton(QWidget *parent) : QPushButton( parent) {
        //constructor sets the geometry of the full screen button
        setGeometry(0,0,100,100);
        setText("Full Screen");
   }

};
#endif // FULL_SCREEN_H

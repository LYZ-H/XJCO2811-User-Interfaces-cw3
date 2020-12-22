#ifndef THE_BUTTON_H
#define THE_BUTTON_H


#include <QPushButton>
#include <QUrl>

class TheButtonInfo {

public:
    QUrl* url; // video file to play
    QIcon* icon; // icon to display
    int indexnum; // index of videos

    TheButtonInfo (QUrl* url, QIcon* icon, int index) : url(url), icon(icon) , indexnum(index){}
};

class TheButton : public QPushButton {
    Q_OBJECT

public:
    TheButtonInfo* info;

     TheButton(QWidget *parent) :  QPushButton(parent) {
         setIconSize(QSize(200,110));
         // if QPushButton clicked...then run clicked() below
         connect(this, SIGNAL(released()), this, SLOT (clicked() ));
    }

    void init(TheButtonInfo* i);

private slots:
    void clicked();
    void searchBtn(QString text);

signals:
    void jumpTo(TheButtonInfo*);

};

#endif //CW2_THE_BUTTON_H

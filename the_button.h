#ifndef THE_BUTTON_H
#define THE_BUTTON_H


#include <QPushButton>
#include <QUrl>

class TheButtonInfo {

public:
    QUrl *url; // video file to play
    QIcon *icon; // icon to display
    int index_num; // index of videos

    TheButtonInfo(QUrl *url, QIcon *icon, int index) : url(url), icon(icon), index_num(index) {}
};

class TheButton : public QPushButton {
Q_OBJECT

public:
    TheButtonInfo *info{};

    explicit TheButton(QWidget *parent) : QPushButton(parent) {
        setIconSize(QSize(200, 110));
        setStyleSheet("QPushButton {\
                           padding: 7px;\
                           border-radius: 10px;\
                           background-color: rgb(255,255,255);\
                       }\
                       QPushButton:hover {\
                           background-color: rgb(215,215,215);\
                           border-color: #444444;\
                       }\
                       QPushButton:pressed {\
                           background-color: rgb(180,180,180);\
                           border-color: #333333;\
                           color: yellow;\
                       }\
                       QPushButton:disabled {\
                           color: #333333;\
                       }");
        // if QPushButton clicked...then run clicked() below
        connect(this, SIGNAL(released()), this, SLOT (clicked()));
    }

    void init(TheButtonInfo *i);

private slots:

    void clicked();

    void searchBtn(const QString &text);

signals:

    void jumpTo(TheButtonInfo *);

};

#endif //CW2_THE_BUTTON_H

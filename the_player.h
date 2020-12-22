#ifndef THE_PLAYER_H
#define THE_PLAYER_H

#include <QApplication>
#include <QMediaPlayer>
#include <vector>
#include <QTimer>
#include <QFileInfo>
#include <QFileDialog>
#include <QDateTime>
#include <QTextEdit>
#include <QLabel>
#include "the_button.h"

using namespace std;

class ThePlayer : public QMediaPlayer {

Q_OBJECT

private:
    vector<TheButtonInfo> *infos{};
    vector<TheButton *> *buttons{};
    QTimer *mTimer;
    long updateCount = 0;
    bool isPause = false;

public:
    size_t video_index = 0;
    QFileInfo file_info;
    QLabel *label = new QLabel();
    QString date;

public:
    ThePlayer() : QMediaPlayer(nullptr) {
        setVolume(0); // be slightly less annoying
        setNotifyInterval(8);
        connect(this, SIGNAL(stateChanged(QMediaPlayer::State)), this,
                SLOT(playStateChanged(QMediaPlayer::State)));
        mTimer = new QTimer(nullptr);
        // 1000ms is one second between ...
        mTimer->setInterval(1000);
        mTimer->start();
    }

    // all buttons have been setup, store pointers here
    void setContent(vector<TheButton *> *b, vector<TheButtonInfo> *i);

    void setPlay(bool flipPlay);

private slots:

    void playStateChanged(QMediaPlayer::State ms);

public slots:

    // start playing this ButtonInfo
    void jumpTo(TheButtonInfo *button);

    void SetPosition(int position); //slot used for our video slider
    void skipBack(bool skip);

    void skipForward(bool skip);

    //slots used for our skip buttons
    void click(); //slot for the play/pause button
    void nextVideo();

    void prevVideo();

    void mouseRelease();

private:
    bool playValue = false;
};

#endif //CW2_THE_PLAYER_H

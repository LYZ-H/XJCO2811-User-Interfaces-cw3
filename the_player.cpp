#include "the_player.h"

using namespace std;

// all buttons have been setup, store pointers here
void ThePlayer::setContent(std::vector<TheButton *> *b, std::vector<TheButtonInfo> *i) {
    buttons = b;
    infos = i;
    jumpTo(buttons->at(0)->info);
}

void ThePlayer::playStateChanged(QMediaPlayer::State ms) {
    if (ms == QMediaPlayer::State::StoppedState) {
        play();
    }
}

void ThePlayer::jumpTo(TheButtonInfo *button) {
    setMedia(*button->url);
    video_index = button->index_num;
    play();
    QString file1 = button->url->toString();
    QString file = file1.right(file1.length() - 8);
    QFileInfo info(file);
    this->file_info = info;
    qint64 size = file_info.size()/1024/1024;//file size, byte
    QString b = tr("%1").arg(size);
    QDateTime created = file_info.birthTime();//created time
    QDateTime lastModified = file_info.lastModified();//last modified time
    QDateTime lastRead = file_info.lastRead();
    label->setText("Name:" + this->file_info.fileName()
                   + " | " + "Size:" + b + " MB" + " | " + "Time:" +
                   created.toString("yyyy-MM-dd hh:mm:ss"));
    date = created.toString("yyyy-MM-dd hh:mm:ss");
}

void ThePlayer::SetPosition(int pos) {
    if(!isPause){
        pause();
    }
    isPause = true;
    setPosition(pos);
}

void ThePlayer::mouseRelease(){
    play();
    isPause = false;
}

void ThePlayer::skipBack(bool skip) {
    if (!skip) {
        setPosition(position() - 5000);
    }
}

//skip by 5 seconds, hence the +-5000
void ThePlayer::skipForward(bool skip) {
    if (!skip) {
        setPosition(position() + 5000);
    }
}

void ThePlayer::setPlay(bool flipPlay) {
    playValue = !flipPlay;
}

void ThePlayer::click() {
    if (playValue) {
        play();
    } else {
        pause();
    }
    setPlay(playValue);
}

void ThePlayer::nextVideo() {
    video_index++;
    if (video_index >= infos->size()) {
        video_index = 0;
    }
    buttons->at(video_index)->click();
}

void ThePlayer::prevVideo() {
        if (video_index == 0) {
            video_index = infos->size() - 1;
        } else {
            video_index--;
        }
    buttons->at(video_index)->click();
}

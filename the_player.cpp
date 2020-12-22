
#include "the_player.h"

using namespace std;

// all buttons have been setup, store pointers here
void ThePlayer::setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i) {
    buttons = b;
    infos = i;
    jumpTo(buttons->at(0)->info);
}

void ThePlayer::playStateChanged(QMediaPlayer::State ms) {
    if(ms == QMediaPlayer::State::StoppedState){
        play();
    }
}

void ThePlayer::jumpTo(TheButtonInfo* button) {
    setMedia(* button->url);
    videoindex = button->indexnum;
    play();
}

void ThePlayer::SetPosition(int pos) {
    setPosition(pos);
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
    videoindex++;
    if (videoindex >= infos->size()) {
        videoindex = 0;
    }
    buttons->at(videoindex)->click();
}

void ThePlayer::prevVideo() {
    if (position() > 1500) {
        setPosition(0);
    } else {
        if (videoindex == 0) {
            videoindex = infos->size() - 1;
        } else {
            videoindex--;
        }
    }
    buttons->at(videoindex)->click();
}

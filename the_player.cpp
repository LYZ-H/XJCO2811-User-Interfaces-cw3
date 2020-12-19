
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

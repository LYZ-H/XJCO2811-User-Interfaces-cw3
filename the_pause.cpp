
#include "the_pause.h"

void PlayButton::setState(QMediaPlayer::State state) {

    //allows the icon to change depending on whether the video is paused or playing
    switch (state) {
        case QMediaPlayer::PlayingState:
            setEnabled(true);
            setIcon(style()->standardIcon(QStyle::SP_MediaPause));
            break;
        case QMediaPlayer::PausedState:
            setEnabled(true);
            setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            break;
        default:
            break;
    }

}
